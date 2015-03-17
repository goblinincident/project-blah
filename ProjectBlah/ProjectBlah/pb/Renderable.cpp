#include <pb\Material.h>

#include <pb\VertexObjectData.h>

#include <pb\Renderable.h>


using namespace glm;

namespace pb
{

	Renderable::Renderable(const char* name) : GameObject(name)
	{
		SetVertexObjectData();
	}

	Renderable::~Renderable()
	{

	}



	void Renderable::SetVertexObjectData()
	{

		// Vertex data //
		vo_data_ = new VertexObjectData[8]
		{
			{ new vec3(-.5f, .5f, .5f) },
			{ new vec3(.5f, .5f, .5f) },
			{ new vec3(-.5f, -.5f, .5f) },
			{ new vec3(.5f, -.5f, .5f) },
			{ new vec3(-.5f, .5f, -.5f) },
			{ new vec3(.5f, .5f, -.5f) },
			{ new vec3(-.5f, -.5f, -.5f) },
			{ new vec3(.5f, -.5f, -.5f) },
		};


		// Index data //
		// front face of cube verts
		unsigned int tl_f = 0; unsigned int tr_f = 1;
		unsigned int bl_f = 2; unsigned int br_f = 3;

		// back face of cube verts
		unsigned int tl_b = 4; unsigned int tr_b = 5;
		unsigned int bl_b = 6; unsigned int br_b = 7;


		index_data_ = new unsigned int[6*2*3]
		{
				tl_f, tr_f, bl_f, tr_f, br_f, bl_f,  // front face
				bl_f, bl_b, tl_b, tl_b, tl_f, bl_f, // left face
				tl_b, tr_b, br_b, br_b, bl_b, tl_b, // back face
				br_f, br_b, tr_b, tr_b, tr_f, br_f, // right face
				tl_f, tr_f, tr_b, tr_b, tl_b, tl_f, // top face
				bl_f, br_f, br_b, br_b, bl_b, bl_f // bottom face
		};
	}


	void Renderable::SetMaterial(Material& material)
	{
		material_ = &material;
		vao_ = material_->CreateVBO(vo_data_);
	}

	void Renderable::Draw()
	{
		if (material_ == nullptr)
			SetMaterial(Material::default_material);
	}


};