

#include <ProjectBlah.h>

#include <pb\Renderable.h>

#include <iostream>

namespace tutorials
{
	class Playground : public ProjectBlah
	{
		pb::Renderable render_test;


		pb::Grid grid;
		pb::CameraFly cam;

	

		void Initialize()
		{
			cam.OpenDebugWindow();
			grid.OpenDebugWindow();
			//cube.OpenDebugWindow();
		}

		void Update()
		{
			render_test.Draw();
		}

		void Shutdown()
		{
		}


	};
};