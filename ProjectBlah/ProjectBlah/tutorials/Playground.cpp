

#include <ProjectBlah.h>

#include <pb\Renderable.h>

#include <iostream>

namespace tutorials
{
	class Playground : public ProjectBlah
	{
	public:
		pb::Renderable render_test;


		pb::Grid grid;
		pb::CameraFly cam;

		Playground() :render_test() {}
		~Playground()
		{
			int i = 0;
			i++;
		}


		void Initialize()
		{
			cam.OpenDebugWindow();
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