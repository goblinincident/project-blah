
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

	pb::TextureManager::instance_ = new pb::TextureManager();

	pb::Material::InitializeStandardMaterials();


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

		pb::GameObject::UpdateAllGameObjects(pb::GameObject::root_node_);

		Update(); // virtual

		Gizmos::draw(cam->projection, cam->view);

		pb::AntTweakHelper::Update();


		glfwSwapBuffers(glfw_win);

	} while (!glfwGetKey(glfw_win, GLFW_KEY_ESCAPE) && !glfwWindowShouldClose(glfw_win));

	Shutdown(); // virtual
}


ProjectBlah::~ProjectBlah()
{
	Gizmos::destroy();

	/// @todo delete pb::Material::default_material;
	delete pb::TextureManager::instance_;
	delete pb::AntTweakHelper::instance_;
	delete pb::Camera::default_camera_;
	delete pb::GameObject::root_node_;
	delete pb::Window::window_;
	
	
	glfwTerminate();
}

