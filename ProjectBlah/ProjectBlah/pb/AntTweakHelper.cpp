

#include <ant\AntTweakBar.h>
#include <glfw\glfw3.h>
#include <pb\Window.h>

#include <pb\AntTweakHelper.h>

namespace pb
{
	AntTweakHelper* AntTweakHelper::instance_ = nullptr;

	AntTweakHelper::AntTweakHelper()
	{
		auto win = Window::GetWindow();


		TwInit(TW_OPENGL, NULL);
		TwDefine(" GLOBAL help="
			"'Descriptions:'");

		TwWindowSize(win->width, win->height);

		
		glfwSetMouseButtonCallback(win->glfw_window, MouseButtonCB);

		glfwSetCursorPosCallback(win->glfw_window, MousePosCB);

		glfwSetScrollCallback(win->glfw_window, MouseScrollCB);

		glfwSetKeyCallback(win->glfw_window, KeyFunCB);
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