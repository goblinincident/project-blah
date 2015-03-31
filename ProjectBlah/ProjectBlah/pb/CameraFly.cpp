
#include <glfw\glfw3.h>
#include <ant\AntTweakBar.h>

#include <string>

#include <pb\CameraFly.h>
#include <pb\Window.h>
#include <pb\Time.h>

namespace pb
{
	CameraFly::CameraFly(const char* name) : Camera(name),
		move_speed(10),
		rotate_speed(6),
		first_press_(true)
	{}


	void CameraFly::Update()
	{
		auto glfw_win = Window::GetGlfwWindow();


		// Movement //
		glm::vec4 desired_pos;

		if (glfwGetKey(glfw_win, GLFW_KEY_W) == GLFW_PRESS)
			desired_pos.z -= move_speed * Time::GetDeltaTime();

		if (glfwGetKey(glfw_win, GLFW_KEY_S) == GLFW_PRESS)
			desired_pos.z += move_speed * Time::GetDeltaTime();

		if (glfwGetKey(glfw_win, GLFW_KEY_A) == GLFW_PRESS)
			desired_pos.x -= move_speed * Time::GetDeltaTime();

		if (glfwGetKey(glfw_win, GLFW_KEY_D) == GLFW_PRESS)
			desired_pos.x += move_speed * Time::GetDeltaTime();

		desired_pos = rotation_matix_local * desired_pos;

		position_local.x += desired_pos.x;
		position_local.y += desired_pos.y;
		position_local.z += desired_pos.z;



		// Rotation // on space pressed
		if (glfwGetMouseButton(glfw_win, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
		{
			if (first_press_)
				glfwSetInputMode(glfw_win, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			else
			{
				glfwGetCursorPos(glfw_win, &cursor_x_, &cursor_y_);

				rotation_local.x -= (float)(cursor_y_ - Window::GetHeight() / 2) * rotate_speed * Time::GetDeltaTime();
				rotation_local.y -= (float)(cursor_x_ - Window::GetWidth() / 2) * rotate_speed * Time::GetDeltaTime();
			}

			glfwSetCursorPos(glfw_win, (double)Window::GetWidth() / 2, (double)Window::GetHeight() / 2);
			first_press_ = false;
		}
		else if (!first_press_)
		{
			first_press_ = true;
			glfwSetInputMode(glfw_win, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}



		Camera::Update();
	}


	void CameraFly::OpenDebugWindow() 
	{
		InititializeDebugWindow(name);

		// help
		std::string bar_setting = "'"; bar_setting += name; bar_setting += "' ";
		bar_setting +=
			"help= 'Use WASD to move camera around the screen.\n"
			"Hold \"RMB\" to rotate with mouse.'";
		TwDefine(bar_setting.c_str());

		// tweakable
		TwAddVarRW(bar, "rotation speed", TW_TYPE_FLOAT, &rotate_speed,
			"min=0 max=20 step=0.1 group='Camera Fly'");

		TwAddVarRW(bar, "movement speed", TW_TYPE_FLOAT, &move_speed,
			"min=0 max=100 step=1 group='Camera Fly'");

		TwAddButton(bar, "reset camera",
			[](void* c){
			auto cam = (CameraFly*)c;
			cam->position_local = glm::vec3(0, 1, 10);
			cam->rotation_local = glm::vec3();
		}, this,"group='Camera Fly'");


		
		GameObject::OpenDebugWindow();
	}

	void CameraFly::CloseDebugWindow()
	{
		TwDeleteBar(bar);
	}
};