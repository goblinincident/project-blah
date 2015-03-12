
#include <glm\ext.hpp>

#include <pb\Window.h>

#include <pb\Camera.h>


using namespace glm;

namespace pb
{

	Camera* Camera::active_camera = nullptr;
	Camera* Camera::default_camera_ = nullptr;



	void Camera::Update()
	{
		if (this != active_camera)
			return;

		view = inverse(transform_matrix_world);
	}




	Camera::Camera(const char* name) : GameObject(name),
		fov(pi<float>() * .25f),
		clip_near(0.1f),
		clip_far(1000.0f),
		view(mat4())
	{
		active_camera = this;

		auto window = Window::GetWindow();
		aspect = ((float)window->width / (float)window->height);

		projection = perspective( fov, aspect, clip_near, clip_far);

		position_local = glm::vec3(0, 1, 10);
	}

};