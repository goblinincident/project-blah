
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
		tiny_shapes_(new vector<tinyobj::shape_t>()),
		materials_(new vector<tinyobj::material_t>())
	{
		obj_path_ = obj_path;
		dir_ = get_dir_from_path(obj_path_);

		std::string err = tinyobj::LoadObj(*tiny_shapes_, *materials_, obj_path_.c_str(), dir_.c_str());

		assert(err == "" && !tiny_shapes_->empty() && "Couldn't load obj shapes!");
	}


	void ObjMesh::Initialize()
	{
		for each (tinyobj::shape_t shape in (*tiny_shapes_))
		{
			Renderable* renderable = new Renderable("obj shape");


			// positions //
			int number_of_verts = shape.mesh.positions.size() / 3;
			vector<vec4>* position_data = new vector<vec4>(number_of_verts);

			for (int i = 0; i < number_of_verts; i++)
			{
				(*position_data)[i].x = shape.mesh.positions[i * 3];
				(*position_data)[i].y = shape.mesh.positions[i * 3 + 1];
				(*position_data)[i].z = shape.mesh.positions[i * 3 + 2];
				(*position_data)[i].w = 1;
			}

			auto attrib_data = &renderable->attribute_config[Material::REQUIREMENTS_ATTRIBUTE_POSITION];
			delete attrib_data->data_pointer;
			attrib_data->data_pointer = &((*position_data)[0]);
			attrib_data->data_element_count = position_data->size();
			attrib_data->data_size = position_data->size() * sizeof(vec4);

			// indicies //
			auto index_data = new vector<unsigned int>(shape.mesh.indices.size());

			for (unsigned int i = 0; i < shape.mesh.indices.size(); i++)
			{
				(*index_data)[i] = shape.mesh.indices[i];
			}

			attrib_data = &renderable->attribute_config[Material::REQUIREMENTS_ATTRIBUTE_INDEX];
			delete attrib_data->data_pointer;
			attrib_data->data_pointer = &((*index_data)[0]);
			attrib_data->data_element_count = index_data->size();
			attrib_data->data_size = index_data->size() * sizeof(unsigned int);
			

			// materials // /// @todo extract materials from obj
			//renderable->BindToMaterial(Material::StandardMaterials::SolidPurple);


			//renderable->AttachParent(this);
			this->AttachChild(renderable);
			renderable_shapes_.push_back(renderable);
		}


	}

	void ObjMesh::Draw()
	{
		for each (Renderable* renderable in renderable_shapes_)
		{
			renderable->Draw();
		}
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




