

#include <ProjectBlah.h>


#include <iostream>

namespace tutorials
{
	class Playground : public ProjectBlah
	{
	public:
		pb::ObjMesh render_test;


		pb::Grid grid;
		pb::CameraFly cam;


		void Initialize()
		{
			//cam.OpenDebugWindow();
			grid.OpenDebugWindow();
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