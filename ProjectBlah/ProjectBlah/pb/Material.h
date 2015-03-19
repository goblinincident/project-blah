#pragma once
#include <string>
#include <glm\glm.hpp>


class ProjectBlah;

namespace pb
{
	class Renderable;


	class Material
	{

		friend class Renderable;

		/** @brief Generates a vertex buffer object for 
		* this material.
		* (called by Renderable)
		**/
		void CreateBuffersForRenderable(Renderable* renderable);

		void DrawRenderable(Renderable* renderable);

	public:

		enum AttributeFlags
		{
			ATTRIBUTE_NONE = 0,
			ATTRIBUTE_POSITION = 1 << 0
		};

		enum UniformFlags
		{
			UNIFORM_NONE = 0,
			UNIFORM_MVP = 1 << 0
		};

		static Material* default_material;

		Material(/*shader options etc*/);

		void SetShader(
			std::string vertex_shader_path = "",
			std::string fragment_shader_path = "",
			unsigned int attribute_flags = AttributeFlags::ATTRIBUTE_POSITION,
			unsigned int uniform_flags = UniformFlags::UNIFORM_MVP);


	private:

		unsigned int attribute_flags_;
		unsigned int uniform_flags_;

		std::string		vertex_shader_path_;
		std::string		vertex_shader_code_;

		std::string		fragment_shader_path_;
		std::string		fragment_shader_code_;

		unsigned int shader_program_id_;





		unsigned int load_shader(const char* shader_source, unsigned int type);
		std::string read_shader(std::string shader_path);
		void check_shader_program(unsigned int program_id);
	};


};