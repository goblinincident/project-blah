
#pragma once

class ProjectBlah;

namespace pb
{

	class Time
	{
		friend class ProjectBlah;

		static void Update(); 


		static float old_;

		static float game_;
		static float delta_;

	public:
		static const float GetGameTime();
		static const float GetDeltaTime();

	};
};