#include <pb\Material.h>

#include <pb\Camera.h>

#include <aie\gl_core_4_4.h>

#include <pb\Renderable.h>


using namespace glm;
using namespace std;

namespace pb
{

	static vector<vec4>* balh = new vector<vec4>{ vec4(0, 0, 0, 1) };

	Renderable::Renderable(const char* name) : GameObject(name),
		attribute_config({
			{ Material::REQUIREMENTS_ATTRIBUTE_POSITION, Renderable::attribute_data{ 0, GL_ARRAY_BUFFER, GL_FLOAT, 1, 4, sizeof(vec4), -1, &((*new vector<vec4>{ vec4(0, 0, 0, 1) })[0]) } },
			{ Material::REQUIREMENTS_ATTRIBUTE_INDEX, Renderable::attribute_data{ 1, GL_ELEMENT_ARRAY_BUFFER, GL_UNSIGNED_INT,1, 1, sizeof(unsigned int), -1, &((*new vector<unsigned int>{ 0 })[0]) } },
			{ Material::REQUIREMENTS_ATTRIBUTE_UV, Renderable::attribute_data{ 2, GL_ARRAY_BUFFER, GL_FLOAT, 1, 2, sizeof(vec2), -1, &((*new vector<vec2>{ vec2(0, 1) })[0]) } } 
			}),
		uniform_config({
			{ Material::REQUIREMENTS_UNIFORM_MVP, Renderable::uniform_data{ "pvm",-1, new mat4(1.0f) } },
			{ Material::REQUIREMENTS_UNIFORM_TEXTURE_DIFFUSE, Renderable::uniform_data{ "texture_diffuse", -1, "./data/texture/default_texture.png" } }
			})
	{
		vertex_array_object_ = -1;
	};

	void Renderable::Initialize()
	{
		if (bound_material_ == nullptr)
			BindToMaterial(Material::StandardMaterials::SolidPurple);
	}

	Renderable::~Renderable()
	{

	}



	void Renderable::BindToMaterial(Material* m)
	{
		m->BindRenderable(this);
	}


	void Renderable::Draw()
	{
		/// @todo move this to Update; //maybe, most likely it's still only gonna get called once per frame.. for now
		if (uniform_config[Material::REQUIREMENTS_UNIFORM_MVP].uniform_location != -1)
		{
			*static_cast<mat4*>(uniform_config[Material::REQUIREMENTS_UNIFORM_MVP].data_pointer) = Camera::active_camera->projection *  Camera::active_camera->view * transform_matrix_world;
		}

		assert(bound_material_ != nullptr && "Material Not set before rendering!");

		bound_material_->DrawRenderable(this);// , Material::DrawStyle::DRAWSTYLE_POINTS);
	}


};