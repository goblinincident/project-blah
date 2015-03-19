
#include <string>
#include <fstream>
#include <vector>

#include <glm\glm.hpp>
#include <aie\gl_core_4_4.h>
#include <glfw\glfw3.h>


#include <pb\Renderable.h>

#include <pb\Material.h>

using namespace std;
using namespace glm;

namespace pb
{
	Material* Material::default_material = nullptr;


	void Material::CreateBuffersForRenderable(Renderable* renderable)
	{
		if (uniform_flags_ & UniformFlags::UNIFORM_MVP)
		{
			glGetUniformLocation(renderable->model_view_projection_id_, "MVP");
		}


		glGenBuffers(1, &renderable->position_buffer_);
		glBindBuffer(GL_ARRAY_BUFFER, renderable->position_buffer_);
		glBufferData(GL_ARRAY_BUFFER, sizeof(renderable->position_data_), renderable->position_data_, GL_STATIC_DRAW);


		glGenBuffers(1, &renderable->index_buffer_);
		glBindFramebuffer(GL_ELEMENT_ARRAY_BUFFER, renderable->index_buffer_);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(renderable->index_data_), renderable->index_data_, GL_STATIC_DRAW);
	}

	void Material::DrawRenderable(Renderable* renderable)
	{
		glUseProgram(shader_program_id_);


		if (uniform_flags_ & UniformFlags::UNIFORM_MVP)
			glUniformMatrix4fv(renderable->model_view_projection_id_, 1, GL_FALSE, &renderable->model_view_projection_[0][0]);


		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, renderable->position_buffer_);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);


		glBindFramebuffer(GL_ELEMENT_ARRAY_BUFFER, renderable->index_buffer_);

		glDrawElements(GL_TRIANGLES, sizeof(renderable->index_data_) / sizeof(unsigned int), GL_UNSIGNED_INT, (void*)0);
	}



	Material::Material()
	{
		SetShader(/*pass from material*/);

	}

	void Material::SetShader(string vertex_shader_path, string fragment_shader_path, unsigned int attribute_flags, unsigned int uniform_flags)
	{
		attribute_flags_ = attribute_flags;
		uniform_flags_ = uniform_flags;



		if (vertex_shader_path.empty())
			vertex_shader_path_ = "./data/shader/basic_position.vert.glsl";

		if (fragment_shader_path.empty())
			fragment_shader_path_ = "./data/shader/solid_purple.frag.glsl";



		vertex_shader_code_ = read_shader(vertex_shader_path_);
		GLuint vertex_shader_id_ = load_shader(vertex_shader_code_.c_str(), GL_VERTEX_SHADER);

		fragment_shader_code_ = read_shader(fragment_shader_path_);
		GLuint fragment_shader_id_ = load_shader(fragment_shader_code_.c_str(), GL_FRAGMENT_SHADER);



		shader_program_id_ = glCreateProgram();

		glAttachShader(shader_program_id_, vertex_shader_id_);
		glAttachShader(shader_program_id_, fragment_shader_id_);


		glLinkProgram(shader_program_id_);
		check_shader_program(shader_program_id_);


		glDeleteShader(vertex_shader_id_);
		glDeleteShader(fragment_shader_id_);
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