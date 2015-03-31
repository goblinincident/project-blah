
#include <glfw\glfw3.h>

#include <ProjectBlah.h>
#include <pb\Time.h>


namespace pb
{
	float Time::old_ = 0;
	float Time::game_ = 0;
	float Time::delta_ = 0;


	void Time::Update()
	{
		game_ = (float)glfwGetTime();
		delta_ = game_ - old_;
		old_ = game_;
	}


	const float Time::GetDeltaTime()
	{
		return delta_;
	}

	const float Time::GetGameTime()
	{
		return game_;
	}
};