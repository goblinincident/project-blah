

#include <ProjectBlah.h>

#include <iostream>

namespace tutorials
{
	class Playground : public ProjectBlah
	{
		pb::Grid grid;
		pb::CameraFly cam;
		pb::Dummy cube;


		void Initialize()
		{
			cam.OpenDebugWindow();
			grid.OpenDebugWindow();
			cube.OpenDebugWindow();
		}

		void Update()
		{
		}

		void Shutdown()
		{
		}


	};
};