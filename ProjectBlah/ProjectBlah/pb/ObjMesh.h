
#pragma once

#include <string>
#include <pb\GameObject.h>
#include <glm\glm.hpp>
#include <vector>


namespace tinyobj{ struct shape_t; struct material_t; };


namespace pb
{
	class Renderable;

	class ObjMesh : public GameObject
	{
		std::vector<tinyobj::shape_t>* tiny_shapes_;
		std::vector<tinyobj::material_t>* materials_;

		std::string dir_;
		std::string obj_path_;


	public:

		ObjMesh(const char* name = "obj mesh", std::string obj_path = "./data/obj/bunny.obj");


		void Draw();


	private:

		std::vector<Renderable*> renderable_shapes_;

		void set_object_data();

		std::string get_dir_from_path(std::string obj_path);
	};


};