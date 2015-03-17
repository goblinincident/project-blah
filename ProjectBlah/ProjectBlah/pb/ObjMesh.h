
#pragma once

#include <pb\GameObject.h>
#include <glm\glm.hpp>
#include <vector>


namespace tinyobj{ struct shape_t; struct material_t; };


namespace pb
{

	class ObjMesh : public GameObject
	{
		std::vector<tinyobj::shape_t>* shapes_;
		std::vector<tinyobj::material_t>* materials_;

		const char* dir_;
		const char* obj_path_;

	public:

		ObjMesh(const char* name = "obj mesh", const char* obj_path = "./data/mesh/bunny.obj");


	private:

		const char* get_dir_from_path(const char* obj_path);
	};


};