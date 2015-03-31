
#include <aie\gl_core_4_4.h>
#include <glfw\glfw3.h>
#include <aie\Gizmos.h>

#include <pb\AntTweakHelper.h>
#include <pb\GameObject.h>

#include <ProjectBlah.h>

ProjectBlah::ProjectBlah()
{
	glfwInit();

	pb::Window::window_instance_ = new pb::Window();

	pb::GameObject::root_node_ = new pb::GameObject("root node");

	pb::Camera::default_camera_ = new pb::Camera();

	pb::AntTweakHelper::ant_tweak_helper_instance_ = new pb::AntTweakHelper();


	ogl_LoadFunctions();


	pb::TextureManager::texture_manager_instance_ = new pb::TextureManager();


	pb::Material::InitializeStandardMaterials();

	Gizmos::create();
}

void ProjectBlah::Run()
{
	Initialize(); // virtual // initialize derrived application.

	auto glfw_win = pb::Window::GetWindow()->glfw_window;
	auto cam = pb::Camera::GetActiveCamera();


	do{
		Gizmos::clear();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwPollEvents();

		pb::Time::Update();

		pb::GameObject::UpdateAllGameObjects(pb::GameObject::root_node_);


		Update(); // virtual // update derived application.


		Gizmos::draw(cam->projection_, cam->view_);

		pb::AntTweakHelper::Update();


		glfwSwapBuffers(glfw_win);

	} while (!glfwGetKey(glfw_win, GLFW_KEY_ESCAPE) && !glfwWindowShouldClose(glfw_win));


	Shutdown(); // virtual // shutdown derived application.
}


ProjectBlah::~ProjectBlah()
{
	Gizmos::destroy();

	/// @todo delete pb::Material::default_material;
	delete pb::TextureManager::texture_manager_instance_;
	delete pb::AntTweakHelper::ant_tweak_helper_instance_;
	delete pb::Camera::default_camera_;
	delete pb::GameObject::root_node_;
	delete pb::Window::window_instance_;
	
	
	glfwTerminate();
}

