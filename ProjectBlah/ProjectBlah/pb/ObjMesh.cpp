
#include <string>
#include <assert.h>

#include <pb\ObjMesh.h>
#include <aie\gl_core_4_4.h>
#include <glfw\glfw3.h>


#include <tinyobj\tiny_obj_loader.h>

using namespace std;

namespace pb
{
	ObjMesh::ObjMesh(const char* name, string obj_path) : GameObject(name)
	{
		obj_path_ = obj_path;
		dir_ = get_dir_from_path(obj_path_);

		std::string err = tinyobj::LoadObj(*shapes_, *materials_, obj_path_.c_str(), dir_.c_str());

		assert(err == "" && !shapes_->empty() && "Couldn't load obj shapes!");
		assert(!materials_->empty() && "Couldn't load materials!");



	}




	string ObjMesh::get_dir_from_path(string obj_path)
	{
		std::string obj_path_string(obj_path);
		std::string dir;

		unsigned int last_slash_idex = obj_path_string.rfind('\\');

		if (last_slash_idex == std::string::npos)	
			last_slash_idex = obj_path_string.rfind('/');

		if (last_slash_idex != std::string::npos)	
			dir = "";

		else										
			dir = obj_path_string.substr(0, last_slash_idex);

		dir += "/";

		return dir.c_str();
	}
};




