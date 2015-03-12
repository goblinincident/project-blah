#pragma once

class ProjectBlah;
struct GLFWwindow;

namespace pb
{
	class AntTweakHelper
	{
		friend class ProjectBlah;

		static AntTweakHelper* instance_;

		AntTweakHelper();
		static void Update();
		~AntTweakHelper();


		static void MouseButtonCB(GLFWwindow*, int button, int action, int mods);

		static void MousePosCB(GLFWwindow*, double x, double y);

		static void KeyFunCB(GLFWwindow* window, int key, int scancode, int action, int mods);

		static void MouseScrollCB(GLFWwindow* window, double x, double y);


	};
};