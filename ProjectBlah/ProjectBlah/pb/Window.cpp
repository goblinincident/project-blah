

#include <iostream>


#include <glfw\glfw3.h>


#include <pb\Window.h>


namespace pb
{
	Window* Window::window_ = nullptr;


	Window::Window() :
		width(800),
		height(600),
		title("Unnamed")
	{
		glfw_window = glfwCreateWindow(
			width, height, title,
			nullptr, nullptr);

		glfwMakeContextCurrent(glfw_window);

		glClearColor(0.1f, 0.1f, 0.25f, 1.0f);

		glEnable(GL_DEPTH_TEST);
	}

	Window::~Window()
	{
		glfwDestroyWindow(glfw_window);
	}


	const Window* Window::GetWindow()
	{
		return window_;
	}


};