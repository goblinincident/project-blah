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

		typedef struct
		{
			static Material* SolidPurple;
			static Material* SolidRed;
			static Material* SimpleTexture;
		}StandardMaterials;


		enum{
			REQUIREMENTS_NONE = 0,
			REQUIREMENTS_ATTRIBUTE_POSITION = 1 << 0,
			REQUIREMENTS_ATTRIBUTE_INDEX = 1 << 1,
			REQUIREMENTS_ATTRIBUTE_UV = 1 << 2,

			REQUIREMENTS_TEXTURE_DIFFUSE = 1 << 20,

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


		Material();

		void BindRenderable(Renderable* r);


		void SetShader(std::string path, ShaderTpes type, unsigned int requirements = REQUIREMENTS_NONE);


		void DrawRenderable(Renderable* r, DrawStyle draw_style = DRAWSTYLE_TRIANGLE);


	private:


		unsigned int requirement_flags_;

		struct shader_data
		{
			std::string path = "";
			std::string code = "";
			unsigned int id = -1;
			unsigned int requirement_flags = 0;
		};
		std::map<const ShaderTpes, shader_data*> shader_data_map;


		unsigned int shader_program_id_;

		void activate_requirements(unsigned int requirement_flags);

		void ready_requirements(Renderable* r, unsigned int attributes);


		unsigned int load_shader(const char* shader_source, unsigned int type);

		std::string read_shader(std::string shader_path);
		void check_shader_program(unsigned int program_id);
	};


};