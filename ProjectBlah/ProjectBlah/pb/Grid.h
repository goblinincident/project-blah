
#pragma once

#include <pb\GameObject.h>
#include <glm\glm.hpp>

namespace pb
{

	class Grid : public GameObject
	{
		static const glm::vec4 white;
		static const glm::vec4 black;

		int size_;
		int spacing_;

	protected:

		void Update(); // virtual


	public:

		Grid(const char* name = "grid");

	};

};