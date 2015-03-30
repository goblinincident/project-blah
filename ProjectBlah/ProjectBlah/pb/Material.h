#pragma once
#include <string>
#include <glm\glm.hpp>
#include <list>
#include <map>

class ProjectBlah;

namespace pb
{
	class Renderable;


	class Material
	{
		friend class ProjectBlah;
		static void InitializeStandardMaterials();
		
		std::list<Renderable*> bound_renderables_;



	public:

		enum{
			REQUIREMENTS_NONE		= 0,
			REQUIREMENTS_ATTRIBUTE_POSITION = 1 << 0,
			REQUIREMENTS_ATTRIBUTE_INDEX = 1 << 1,

			REQUIREMENTS_UNIFORM_COLOUR = 1 << 29,
			REQUIREMENTS_UNIFORM_MVP = 1 << 30,
			REQUIREMENTS_UNIFORM_TEXTURE_DIFFUSE = 1 << 31
		};
		enum ShaderTpes
		{
			SHADERTYPE_VERTEX = 0x8B31,
			SHADERTYPE_FRAGMENT = 0x8B30
		};
		enum DrawStyle
		{
			DRAWSTYLE_TRIANGLE = 0x0004,
			DRAWSTYLE_POINTS = 0x0000
		};




		typedef struct
		{
			static Material* SolidPurple;
			static Material* SolidRed;
		}StandardMaterials;


		Material();

		void BindRenderable(Renderable* r);


		void SetShader(std::string path, ShaderTpes type, unsigned int requirements = REQUIREMENTS_NONE );


		void DrawRenderable(Renderable* r, DrawStyle draw_style = DRAWSTYLE_TRIANGLE);


	private:
		void activate_requirements(unsigned int requirement_flags);

		struct shader_data
		{
			std::string path = "";
			std::string code = "";
			unsigned int id = -1;
			unsigned int requirement_flags = 0;
		};

		unsigned int shader_program_id_;

		unsigned int requirement_flags_;

		std::map<const ShaderTpes, shader_data*> shader_data_map;

		shader_data* shader_data_vertex_;
		shader_data* shader_data_fragment_;

		
		void ready_requirements(Renderable* r, unsigned int attributes);

		unsigned int load_shader(const char* shader_source, unsigned int type);
		std::string read_shader(std::string shader_path);
		void check_shader_program(unsigned int program_id);
	};


};