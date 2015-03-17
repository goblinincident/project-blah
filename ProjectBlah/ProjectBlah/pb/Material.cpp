
#include <string>
#include <fstream>
#include <vector>

#include <aie\gl_core_4_4.h>
#include <glfw\glfw3.h>


#include <pb\Renderable.h>

#include <pb\Material.h>

using namespace std;

namespace pb
{
	Material Material::default_material = Material();


	unsigned int Material::CreateVBO(VertexObjectData* vo_data)
	{


	}


	Material::Material()
	{
		SetShader(/*pass from material*/);

	}

	void Material::SetShader(const char* vertex_shader_path, const char* fragment_shader_path, unsigned int attribute_flags, unsigned int uniform_flags)
	{
		attribute_flags_ = attribute_flags;
		uniform_flags_ = uniform_flags;



		if (vertex_shader_path == nullptr)
			vertex_shader_path_ = "./data/shader/basic_position.vert.glsl";

		if (fragment_shader_path == nullptr)
			fragment_shader_path_ = "./data/shader/solid_purple.frag.glsl";



		vertex_shader_code_ = read_shader(vertex_shader_path_);
		GLuint vertex_shader_id_ = load_shader(vertex_shader_code_, GL_VERTEX_SHADER);

		fragment_shader_code_ = read_shader(fragment_shader_path_);
		GLuint fragment_shader_id_ = load_shader(fragment_shader_code_, GL_FRAGMENT_SHADER);



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
		if (log_length > 0){
			vector<char> err_msg(log_length + 1);
			glGetShaderInfoLog(shader_id, log_length, NULL, &err_msg[0]);
			printf("%s\n", &err_msg[0]);
			assert(!"Could't load shader!");
		}

		return shader_id;
	}

	const char* Material::read_shader(const char* shader_path)
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
		if (log_length > 0){
			std::vector<char> err_msg(log_length + 1);
			glGetProgramInfoLog(program_id, log_length, NULL, &err_msg[0]);
			printf("%s\n", &err_msg[0]);
			assert(!"Shader program's fucked!");
		}

	}
};