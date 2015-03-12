


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
		static Window* window_;
		Window();
		~Window();


	public:

		static const Window* GetWindow();


		GLFWwindow* glfw_window;

		int width;
		int height;
		const char* title;
	};

}