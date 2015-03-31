#pragma once

#include <glm\glm.hpp>
#include <pb\GameObject.h>
#include <vector>
#include <map>

class ProjectBlah;

namespace pb
{
	class Material;

	class Renderable : public GameObject
	{
		
	protected:
		void Initialize();
	public:
		struct attribute_data
		{
			unsigned int attribute_location;
			unsigned int gl_buffer_type;
			unsigned int gl_element_type;
			unsigned int data_element_count;
			unsigned int data_sub_element_count;
			unsigned int data_size;
			unsigned int buffer_id;
			void* data_pointer;
		};

		struct uniform_data
		{
			std::string uniform_name;
			unsigned int uniform_location;
			void* data_pointer;
		};

		struct texture_data
		{
			texture_data(std::string uniform_name, unsigned int gl_texture_slot, unsigned int texture_slot, std::string path) :
			uniform_name(uniform_name),
			gl_texture_slot(gl_texture_slot),
			texture_slot(texture_slot),
			path(path){}

			const std::string uniform_name;
			const unsigned int gl_texture_slot;
			const unsigned int texture_slot;
			std::string path;
			int width = -1;
			int height = -1;
			unsigned int gl_texture_id = -1;
			unsigned int uniform_location = -1;
		};


		std::map<const unsigned int, attribute_data>attribute_config;
		std::map<const unsigned int, uniform_data>uniform_config;
		std::map<const unsigned int, texture_data>texture_config;

		unsigned int vertex_array_object_;
		Material* bound_material_ = nullptr;



		Renderable(const char* name = "renderable");

		~Renderable();

		void Draw();

		void BindToMaterial(Material* m);


	};





}