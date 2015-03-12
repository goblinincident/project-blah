
#pragma once

class ProjectBlah;

namespace pb
{

	class Time
	{
		friend class ProjectBlah;

		static void Update(); 


		static float old_;


	public:

		static float game;
		static float delta;
	};
};