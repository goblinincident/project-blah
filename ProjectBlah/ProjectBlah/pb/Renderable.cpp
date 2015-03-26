#include <pb\Material.h>

#include <pb\Camera.h>

#include <pb\Renderable.h>


using namespace glm;
using namespace std;

namespace pb
{

	Renderable::Renderable(const char* name) : GameObject(name)
	{
		set_renderable_defaults();
	}

	Renderable::~Renderable()
	{

	}




	void Renderable::set_renderable_defaults()
	{
		// Vertex data //
		position_data_ = vector<vec4>(8);

		position_data_[0] = vec4(-.5f, .5f, .5f, 1.0f);
		position_data_[1] = vec4(.5f, .5f, .5f, 1.0f);
		position_data_[2] = vec4(-.5f, -.5f, .5f, 1.0f);
		position_data_[3] = vec4(.5f, -.5f, .5f, 1.0f);
		position_data_[4] = vec4(-.5f, .5f, -.5f, 1.0f);
		position_data_[5] = vec4(.5f, .5f, -.5f, 1.0f);
		position_data_[6] = vec4(-.5f, -.5f, -.5f, 1.0f);
		position_data_[7] = vec4(.5f, -.5f, -.5f, 1.0f);


		// Index data //
		// front face of cube verts
		unsigned int tl_f = 0; unsigned int tr_f = 1;
		unsigned int bl_f = 2; unsigned int br_f = 3;

		// back face of cube verts
		unsigned int tl_b = 4; unsigned int tr_b = 5;
		unsigned int bl_b = 6; unsigned int br_b = 7;

		index_data_ = vector<unsigned int>
		{
			tl_f, tr_f, bl_f, tr_f, br_f, bl_f,  // front face
				bl_f, bl_b, tl_b, tl_b, tl_f, bl_f, // left face
				tl_b, tr_b, br_b, br_b, bl_b, tl_b, // back face
				br_f, br_b, tr_b, tr_b, tr_f, br_f, // right face
				tl_f, tr_f, tr_b, tr_b, tl_b, tl_f, // top face
				bl_f, br_f, br_b, br_b, bl_b, bl_f // bottom face
		};

		
	}


	void Renderable::SetMaterial(Material* material)
	{
		active_material_ = material;
		active_material_->CreateRequiredBuffers(this);
	}

	void Renderable::Draw()
	{
		model_view_projection_ = Camera::active_camera->projection *  Camera::active_camera->view * transform_matrix_world;

		assert(active_material_ != nullptr && "Material Not set before rendering!");

		active_material_->DrawRenderable(this);
	}


};