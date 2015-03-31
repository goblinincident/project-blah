

#include <ant\AntTweakBar.h>
#include <glfw\glfw3.h>
#include <pb\Window.h>

#include <pb\AntTweakHelper.h>

namespace pb
{
	AntTweakHelper* AntTweakHelper::ant_tweak_helper_instance_ = nullptr;

	AntTweakHelper::AntTweakHelper()
	{

		TwInit(TW_OPENGL, NULL);
		TwDefine(" GLOBAL help="
			"'Descriptions:'");

		TwWindowSize(Window::GetWidth(), Window::GetHeight());

		auto glfw_window = Window::GetGlfwWindow();
		
		glfwSetMouseButtonCallback(glfw_window, MouseButtonCB);

		glfwSetCursorPosCallback(glfw_window, MousePosCB);

		glfwSetScrollCallback(glfw_window, MouseScrollCB);

		glfwSetKeyCallback(glfw_window, KeyFunCB);
	}


	void AntTweakHelper::Update()
	{
		TwDraw();
	}


	AntTweakHelper::~AntTweakHelper()
	{
		TwTerminate();
	}


	void AntTweakHelper::MouseButtonCB(GLFWwindow* win, int button, int action, int mods)
	{
		TwEventMouseButtonGLFW(button, action);
	}

	void AntTweakHelper::MousePosCB(GLFWwindow* win, double x, double y)
	{
		TwEventMousePosGLFW((int)x, (int)y);
	}

	void AntTweakHelper::KeyFunCB(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		TwEventKeyGLFW(key, action);
		TwEventCharGLFW(key, action);
	}

	void AntTweakHelper::MouseScrollCB(GLFWwindow* window, double x, double y)
	{
		TwEventMouseWheelGLFW((int)y);
	}


};