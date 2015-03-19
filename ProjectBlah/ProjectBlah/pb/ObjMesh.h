
#pragma once

#include <string>
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

		std::string dir_;
		std::string obj_path_;

	public:

		ObjMesh(const char* name = "obj mesh", std::string obj_path = "./data/mesh/bunny.obj");


	private:

		std::string get_dir_from_path(std::string obj_path);
	};


};