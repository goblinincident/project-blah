
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


	void Material::CreateBuffersForRenderable(Renderable* r)
	{
		glBindAttribLocation(shader_program_id_, Attributes::ATTRIBUTE_POSITION, "Position");


		//glGenBuffers(1, &r->position_buffer_id_);

		//glBindBuffer(GL_ARRAY_BUFFER, r->position_buffer_id_);
		//glBufferData(GL_ARRAY_BUFFER, r->position_data_.size() * sizeof(vec4), &r->position_data_[0], GL_STATIC_DRAW);
		//glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Material::DrawRenderable(Renderable* r)
	{
		
		//glUseProgram(shader_program_id_);

		////glBindBuffer(GL_ARRAY_BUFFER, r->position_buffer_id_);
		//glBindVertexBuffer(1, 1, r->position_buffer_id_, 4);

		//glEnableVertexAttribArray(Attributes::ATTRIBUTE_POSITION);

		//glVertexAttribPointer(Attributes::ATTRIBUTE_POSITION, 1, GL_FLOAT, GL_FALSE, 0, 0);
	

	
		//glDrawArrays(GL_TRIANGLES, 0, 3);
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


		//glDeleteShader(vertex_shader_id_);
		//glDeleteShader(fragment_shader_id_);
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