#pragma once

#include <pb\GameObject.h>

namespace pb
{
	class Dummy : public GameObject
	{
		
	public:
		Dummy(const char* name = "dummy");
		
		void Update(); // virtual
	};

};