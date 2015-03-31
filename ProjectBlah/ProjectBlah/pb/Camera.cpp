
#include <glm\ext.hpp>

#include <pb\Window.h>

#include <pb\Camera.h>


using namespace glm;

namespace pb
{

	Camera* Camera::active_camera_ = nullptr;
	Camera* Camera::default_camera_ = nullptr;



	void Camera::Update()
	{
		if (this != active_camera_)
			return;

		view_ = inverse(transform_matrix_world);
	}




	Camera::Camera(const char* name) : GameObject(name),
		fov_(pi<float>() * .25f),
		clip_near_(0.1f),
		clip_far_(1000.0f),
		view_(mat4())
	{
		active_camera_ = this;
		auto window = Window::GetWindow();
		aspect_ = ((float)window->width / (float)window->height);
		projection_ = perspective(fov_, aspect_, clip_near_, clip_far_);
		position_local = glm::vec3(0, 1, 10);
	}




	const Camera* Camera::GetDefaultCamera()
	{
		return default_camera_;
	}

	const Camera* Camera::GetActiveCamera()
	{
		return active_camera_;
	}


	const float Camera::GetFov() const
	{
		return fov_;
	}

	const float Camera::GetAspect() const
	{
		return aspect_;
	}

	const float Camera::GetClipNear() const
	{
		return clip_near_;
	}

	const float Camera::GetClipFar() const
	{
		return clip_far_;
	}

	const mat4& Camera::GetView() const
	{
		return view_;
	}

	const mat4& Camera::GetProjection() const
	{
		return projection_;
	}
};