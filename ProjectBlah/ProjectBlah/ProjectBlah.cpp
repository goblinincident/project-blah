
#include <aie\gl_core_4_4.h>
#include <glfw\glfw3.h>
#include <aie\Gizmos.h>

#include <pb\AntTweakHelper.h>
#include <pb\GameObject.h>

#include <ProjectBlah.h>

ProjectBlah::ProjectBlah()
{
	glfwInit();
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);


	auto win = pb::Window::window_ = new pb::Window();

	pb::GameObject::root_node_ = new pb::GameObject("root node");

	pb::Camera::default_camera_ = new pb::Camera();

	pb::AntTweakHelper::instance_ = new pb::AntTweakHelper();


	ogl_LoadFunctions();

	pb::Material::default_material = new pb::Material();


	Gizmos::create();
}

void ProjectBlah::Run()
{

	Initialize(); // virtual

	auto glfw_win = pb::Window::window_->glfw_window;
	auto cam = pb::Camera::active_camera;


	do{
		Gizmos::clear();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwPollEvents();

		pb::Time::Update();

		Update(); // virtual

		pb::GameObject::UpdateAllGameObjects(pb::GameObject::root_node_);


		Gizmos::draw(cam->projection, cam->view);

		pb::AntTweakHelper::Update();


		glfwSwapBuffers(glfw_win);

	} while (!glfwGetKey(glfw_win, GLFW_KEY_ESCAPE) && !glfwWindowShouldClose(glfw_win));

	Shutdown(); // virtual
}


ProjectBlah::~ProjectBlah()
{
	delete pb::Material::default_material;
	delete pb::Camera::default_camera_;
	delete pb::GameObject::root_node_;
	delete pb::Window::window_;
	delete pb::AntTweakHelper::instance_;

	Gizmos::destroy();
	
	glfwTerminate();
}

