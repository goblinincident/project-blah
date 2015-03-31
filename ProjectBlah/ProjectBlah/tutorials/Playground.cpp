

#include <glfw\glfw3.h>

#include <ProjectBlah.h>

#include <iostream>

namespace tutorials
{
	class Playground : public ProjectBlah
	{
	public:
		pb::ObjMesh render_test;

		//pb::Grid grid;
		pb::CameraFly cam;


		void Initialize()
		{
			//cam.OpenDebugWindow();
			//grid.OpenDebugWindow();

			render_test.OpenDebugWindow();
		}

		bool pressed_test = false;
		void Update()
		{
			render_test.Draw();

			//if (glfwGetKey(pb::Window::GetWindow()->glfw_window, GLFW_KEY_SPACE) == GLFW_PRESS)
			//{
			//	if (!pressed_test)
			//		render_test.BindToMaterial(pb::Material::StandardMaterials::SolidRed);
			//	pressed_test = true;
			//}
			//else if (pressed_test)
			//{
			//	render_test.BindToMaterial(pb::Material::StandardMaterials::SolidPurple);
			//	pressed_test = false;
			//}


			if (glfwGetKey(pb::Window::GetWindow()->glfw_window, GLFW_KEY_T) == GLFW_PRESS)
			{
				//pb::Material::StandardMaterials::SolidPurple->SetShader("./data/shader/solid_red.frag.glsl", pb::Material::SHADERTYPE_FRAGMENT);
			
			}

		}

		void Shutdown()
		{

		}


	};
};