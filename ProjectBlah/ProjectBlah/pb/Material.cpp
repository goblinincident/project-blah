
#include <string>
#include <fstream>
#include <vector>

#include <glm\glm.hpp>
#include <glm\ext.hpp>
#include <aie\gl_core_4_4.h>
#include <glfw\glfw3.h>


#include <pb\Renderable.h>

#include <pb\Material.h>
#include <pb\TextureManager.h>

using namespace std;
using namespace glm;

namespace pb
{
	Material* Material::StandardMaterials::SolidPurple = nullptr;
	Material* Material::StandardMaterials::SolidRed = nullptr;
	Material* Material::StandardMaterials::SimpleTexture = nullptr;


	void Material::InitializeStandardMaterials()
	{
		Material* mat;

		mat = new Material();
		mat->SetShader("./data/shader/basic_position.vert.glsl", SHADERTYPE_VERTEX,
			REQUIREMENTS_ATTRIBUTE_POSITION |
			REQUIREMENTS_ATTRIBUTE_INDEX |
			REQUIREMENTS_UNIFORM_MVP);
		mat->SetShader("./data/shader/solid_red.frag.glsl", pb::Material::SHADERTYPE_FRAGMENT);
		StandardMaterials::SolidRed = mat;

		mat = new Material();
		mat->SetShader("./data/shader/basic_position.vert.glsl", SHADERTYPE_VERTEX,
			REQUIREMENTS_ATTRIBUTE_POSITION |
			REQUIREMENTS_ATTRIBUTE_INDEX |
			REQUIREMENTS_UNIFORM_MVP);
		mat->SetShader("./data/shader/solid_purple.frag.glsl", SHADERTYPE_FRAGMENT);
		StandardMaterials::SolidPurple = mat;

		mat = new Material();
		mat->SetShader("./data/shader/basic_texture.vert.glsl", SHADERTYPE_VERTEX,
			REQUIREMENTS_ATTRIBUTE_POSITION |
			REQUIREMENTS_ATTRIBUTE_INDEX |
			REQUIREMENTS_ATTRIBUTE_UV |
			REQUIREMENTS_UNIFORM_MVP);
		mat->SetShader("./data/shader/basic_texture.frag.glsl", SHADERTYPE_FRAGMENT,
			REQUIREMENTS_TEXTURE_0_DIFFUSE |
			REQUIREMENTS_TEXTURE_1_DIFFUSE);
		StandardMaterials::SimpleTexture = mat;
	}



	Material::Material() :
		requirement_flags_(0),
		shader_data_map(map<const Material::ShaderTpes, Material::shader_data*>({
			{ SHADERTYPE_VERTEX, nullptr },
			{ SHADERTYPE_FRAGMENT, nullptr }
	}))
	{
		shader_program_id_ = glCreateProgram();
	}


	void Material::BindRenderable(Renderable* r)
	{
		if (r->bound_material_ == this)  return;

		if (r->bound_material_ != nullptr)
			r->bound_material_->bound_renderables_.remove(r);

		bound_renderables_.push_back(r);

		r->bound_material_ = this;

		if (r->vertex_array_object_ == -1)
			glGenVertexArrays(1, &r->vertex_array_object_);

		ready_requirements(r, requirement_flags_);
	}


	void Material::SetShader(string path, Material::ShaderTpes type, unsigned int requirements)
	{

		shader_data* data = shader_data_map[type];

		if (data == nullptr)
			data = new shader_data();

		if (data->path == path) return;

		glDetachShader(shader_program_id_, data->id);


		data->path = path;
		data->code = read_shader(path);
		data->id = load_shader(data->code.c_str(), type);

		glAttachShader(shader_program_id_, data->id);
		glDeleteShader(data->id);

		glLinkProgram(shader_program_id_);
		check_shader_program(shader_program_id_);


		activate_requirements(requirements);

		shader_data_map[type] = data;
	}


	void Material::DrawRenderable(Renderable* r, Material::DrawStyle draw_style)
	{
		assert(shader_data_map[SHADERTYPE_VERTEX] != nullptr && "No vertex shader loaded!");
		assert(shader_data_map[SHADERTYPE_FRAGMENT] != nullptr && "No fragment shader loaded!");


		glUseProgram(shader_program_id_);

		glBindVertexArray(r->vertex_array_object_);


		if (requirement_flags_ & REQUIREMENTS_UNIFORM_MVP)
		{
			auto data = &r->uniform_config[REQUIREMENTS_UNIFORM_MVP];
			glUniformMatrix4fv(data->uniform_location, 1, GL_FALSE, value_ptr(*static_cast<mat4*>(data->data_pointer)));
		}


		if (requirement_flags_ & REQUIREMENTS_TEXTURE_0_DIFFUSE)
		{
			//auto data = &r->texture_config[REQUIREMENTS_TEXTURE_0_DIFFUSE];
			//glActiveTexture(data->gl_texture_slot);

		/*	glUniform1i(data->uniform_location, data->gl_texture_slot);
			glActiveTexture(data->gl_texture_slot)*/;
			//glBindTexture(GL_TEXTURE_2D, data->gl_texture_id);
		}



		if (draw_style == DRAWSTYLE_TRIANGLE && r->attribute_config[REQUIREMENTS_ATTRIBUTE_POSITION].data_element_count < 3)
			draw_style = DRAWSTYLE_POINTS;


		if (requirement_flags_ & REQUIREMENTS_ATTRIBUTE_INDEX)
		{
			auto data = &r->attribute_config[REQUIREMENTS_ATTRIBUTE_INDEX];
			glBindBuffer(data->gl_buffer_type, data->buffer_id);
			glDrawElements(draw_style, data->data_element_count, data->gl_element_type, 0);
		}
		else if (requirement_flags_ & REQUIREMENTS_ATTRIBUTE_POSITION)
		{
			auto data = &r->attribute_config[REQUIREMENTS_ATTRIBUTE_POSITION];
			glBindBuffer(data->gl_buffer_type, data->buffer_id);
			glDrawArrays(draw_style, 0, data->data_element_count);
		}
		else
			assert(!"Attempted to draw with materieal that has no index or position attributes!");
	}



	void Material::activate_requirements(unsigned int requirement_flags)
	{
		unsigned int new_requirements = (requirement_flags & requirement_flags_) ^ requirement_flags;

		if (new_requirements)
		{
			requirement_flags_ = requirement_flags_ | new_requirements;
			for each (Renderable* r in bound_renderables_)
				ready_requirements(r, new_requirements);
		}
	}


	void Material::ready_requirements(Renderable* r, unsigned int attributes)
	{
		glBindVertexArray(r->vertex_array_object_);

		// attributes //
		for (auto iter = r->attribute_config.begin(); iter != r->attribute_config.end(); iter++)
		{
			auto flag = (*iter).first;

			if (requirement_flags_ & flag)
			{
				auto data = &(*iter).second;

				if (data->buffer_id == -1)
					glGenBuffers(1, &data->buffer_id);

				glBindBuffer(data->gl_buffer_type, data->buffer_id);
				glBufferData(data->gl_buffer_type, data->data_size, data->data_pointer, GL_STATIC_DRAW);
				glVertexAttribPointer(data->attribute_location, data->data_sub_element_count, data->gl_element_type, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(data->attribute_location);
			}
		}

		// uniforms //
		for (auto iter = r->uniform_config.begin(); iter != r->uniform_config.end(); iter++)
		{
			auto flag = (*iter).first;
			if (requirement_flags_ & flag)
			{
				auto data = &(*iter).second;
				data->uniform_location = glGetUniformLocation(shader_program_id_, data->uniform_name.c_str());
			}
		}

		// textures //
		glUseProgram(shader_program_id_);

		for (auto iter = r->texture_config.begin(); iter != r->texture_config.end(); iter++)
		{
			auto flag = (*iter).first;
			if (requirement_flags_ & flag)
			{
				auto data = &(*iter).second;

				data->gl_texture_id = TextureManager::GetTextureId(data->path);
				data->width = TextureManager::GetTextureWidth(data->path);
				data->height = TextureManager::GetTextureHeight(data->path);
				data->uniform_location = glGetUniformLocation(shader_program_id_, data->uniform_name.c_str());
				if (data->uniform_location != -1)
				{
					glUniform1i(data->uniform_location, data->gl_texture_slot);
					glActiveTexture(data->gl_texture_slot);
					glBindTexture(GL_TEXTURE_2D, data->gl_texture_id);
				}
			}
		}


	}


	unsigned int Material::load_shader(const char* shader_source, unsigned int type)
	{
		GLuint shader_id = glCreateShader(type);

		glShaderSource(shader_id, 1, &shader_source, NULL);
		glCompileShader(shader_id);


		GLint result = GL_FALSE;
		int log_length;

		glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
		glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_length);
		if (log_length > 1){
			vector<char> err_msg(log_length + 1);
			glGetShaderInfoLog(shader_id, log_length, NULL, &err_msg[0]);
			printf("%s\n", &err_msg[0]);
			assert(!"Could't load shader!");
		}

		return shader_id;
	}

	string Material::read_shader(string shader_path)
	{
		string shader_code;
		ifstream shader_stream(shader_path, ios::in);

		if (shader_stream.is_open())
		{
			string Line = "";
			while (getline(shader_stream, Line))
				shader_code += "\n" + Line;
			shader_stream.close();
		}
		else
			assert(!"Couldn't open shader file!");

		return shader_code.c_str();
	}

	void Material::check_shader_program(unsigned int program_id)
	{
		GLint result = GL_FALSE;
		int log_length;

		glGetProgramiv(program_id, GL_LINK_STATUS, &result);
		glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &log_length);
		if (log_length > 1){
			std::vector<char> err_msg(log_length + 1);
			glGetProgramInfoLog(program_id, log_length, NULL, &err_msg[0]);
			printf("%s\n", &err_msg[0]);
			assert(!"Shader program's fucked!");
		}

	}


};