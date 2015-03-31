


/** @file Window.h 
* @brief Represents a gl window
**/

#pragma once

struct GLFWwindow;
class ProjectBlah;

namespace pb
{
	class Window
	{
		friend class ProjectBlah;
		static Window* window_instance_;
		Window();
		~Window();

		GLFWwindow* glfw_window_;

		unsigned int width_;
		unsigned int height_;
		const char* title_;

	public:

		static GLFWwindow* GetGlfwWindow();
		static const unsigned int GetWidth();
		static const unsigned int GetHeight();
		static const char* GetTitle();
	};

}