


#pragma once

#include <pb\DebugWindow.h>
#include <pb\Camera.h>

namespace pb
{
	class CameraFly : public Camera, virtual public DebugWindow
	{

		bool first_press_;
		double cursor_x_, cursor_y_;

	protected:

		void Update(); // virtual


	public:

		CameraFly(const char* name = "camera fly");


		void OpenDebugWindow(); // virtual
		void CloseDebugWindow(); // virtual


		float move_speed;
		float rotate_speed;

	};

};