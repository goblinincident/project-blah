
#include <string>
#include <assert.h>

#include <pb\ObjMesh.h>
#include <pb\Material.h>
#include <pb\Renderable.h>


#include <tinyobj\tiny_obj_loader.h>

using namespace std;
using namespace glm;

namespace pb
{
	ObjMesh::ObjMesh(const char* name, string obj_path) : GameObject(name),
		shapes_(new vector<tinyobj::shape_t>()),
		materials_(new vector<tinyobj::material_t>())
	{
		obj_path_ = obj_path;
		dir_ = get_dir_from_path(obj_path_);

		std::string err = tinyobj::LoadObj(*shapes_, *materials_, obj_path_.c_str(), dir_.c_str());

		assert(err == "" && !shapes_->empty() && "Couldn't load obj shapes!");


		set_default_object_data();
	}


	void ObjMesh::Draw()
	{
		shape_renderable_->Draw();
	}


	void ObjMesh::set_default_object_data() // virtual
	{
		shape_renderable_ = new Renderable();


		// positions //
		int number_of_verts = (*shapes_)[0].mesh.positions.size() / 3;
		shape_renderable_->position_data_ = vector<vec4>(number_of_verts);
		for (int i = 0; i < number_of_verts; i++)
		{
			shape_renderable_->position_data_[i].x = (*shapes_)[0].mesh.positions[i * 3];
			shape_renderable_->position_data_[i].y = (*shapes_)[0].mesh.positions[i * 3 + 1];
			shape_renderable_->position_data_[i].z = (*shapes_)[0].mesh.positions[i * 3 + 2];
			shape_renderable_->position_data_[i].w = 1;
		}

		// indicies //
		shape_renderable_->index_data_ = vector<unsigned int>((*shapes_)[0].mesh.indices.size());
		for (int i = 0; i < (*shapes_)[0].mesh.indices.size(); i++)
		{
			shape_renderable_->index_data_[i] = (*shapes_)[0].mesh.indices[i];
		}


		shape_renderable_->SetMaterial(Material::default_material);
	}




	string ObjMesh::get_dir_from_path(string obj_path)
	{
		std::string obj_path_string(obj_path);
		std::string dir;

		unsigned int last_slash_idex = obj_path_string.rfind('\\');

		if (last_slash_idex == std::string::npos)
			last_slash_idex = obj_path_string.rfind('/');

		if (last_slash_idex == std::string::npos)
			dir = "";

		else
			dir = obj_path_string.substr(0, last_slash_idex);

		dir += "/";

		return dir.c_str();
	}
};




