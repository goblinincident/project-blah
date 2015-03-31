

#include <iostream>


#include <glfw\glfw3.h>


#include <pb\Window.h>


namespace pb
{
	Window* Window::window_instance_ = nullptr;


	Window::Window() :
		width_(800),
		height_(600),
		title_("Unnamed")
	{
		glfw_window_ = glfwCreateWindow(
			width_, height_, title_,
			nullptr, nullptr);

		glfwMakeContextCurrent(glfw_window_);

		glClearColor(0.1f, 0.1f, 0.25f, 1.0f);

		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
		glEnable(GL_DEPTH_TEST);
	}

	Window::~Window()
	{
		glfwDestroyWindow(glfw_window_);
	}


	GLFWwindow* Window::GetGlfwWindow()
	{
		return window_instance_->glfw_window_;
	}

	const unsigned int Window::GetWidth()
	{
		return window_instance_->width_;
	}

	const unsigned int Window::GetHeight()
	{
		return window_instance_->height_;
	}

	const char* Window::GetTitle()
	{
		return window_instance_->title_;
	}
};