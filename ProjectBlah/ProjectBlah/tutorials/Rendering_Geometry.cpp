

#include <ProjectBlah.h>

#include <iostream>

namespace tutorials
{

	/** @brief
	* A basic scene represented by a grid and a
	* fly-camera.
	* (use WASD with RMB to navigate the scene)
	**/
	class Rendering_Geometry : public ProjectBlah
	{
		pb::Grid grid;
		pb::CameraFly cam;
		pb::ObjMesh default_mesh;

		void Initialize()
		{
			default_mesh.OpenDebugWindow();
		}

		void Update()
		{
			default_mesh.Draw();
		}

		void Shutdown()
		{}
	};
};