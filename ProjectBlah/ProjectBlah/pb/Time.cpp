
#include <glfw\glfw3.h>

#include <ProjectBlah.h>
#include <pb\Time.h>


namespace pb
{
	float Time::old_ = 0;
	float Time::game = 0;
	float Time::delta = 0;


	void Time::Update()
	{
		game = (float)glfwGetTime();
		delta = game - old_;
		old_ = game;
	}
};