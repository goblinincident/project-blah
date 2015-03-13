

#include <ProjectBlah.h>

#include <iostream>

namespace tutorials
{

	/** @brief
	* A basic scene represented by a grid and a 
	* fly-camera.
	* (use WASD with RMB to navigate the scene)
	**/
	class Cameras_and_Projections : public ProjectBlah
	{
		pb::Grid grid;
		pb::CameraFly cam;

		void Initialize()
		{
			cam.OpenDebugWindow();
		}

		void Update()
		{}

		void Shutdown()
		{}
	};
};