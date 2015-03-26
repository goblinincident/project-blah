#pragma once

#include <glm\glm.hpp>
#include <pb\GameObject.h>
#include <vector>

class ProjectBlah;

namespace pb
{

	class Material;

	class Renderable : public GameObject
	{
	public:

		Renderable(const char* name = "renderable");

		~Renderable();

		void Draw();

		void SetMaterial(Material* material);

		std::vector<glm::vec4> position_data_;
		std::vector<unsigned int> index_data_;

		unsigned int vertex_array_object_;
		unsigned int index_buffer_id_;
		unsigned int position_buffer_id_;


		glm::mat4 model_view_projection_;

		unsigned int model_view_projection_id_;

		/// @todo Put the rest of the possible vertex info here


	private:

		Material* active_material_ = nullptr;

		void set_renderable_defaults();

	};





}