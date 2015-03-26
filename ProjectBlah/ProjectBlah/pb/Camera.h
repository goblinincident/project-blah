


#pragma once

#include <glm\glm.hpp>
#include <pb\GameObject.h>

class ProjectBlah;

namespace pb
{
	class Camera : public GameObject
	{
		friend class ProjectBlah;
		static Camera* default_camera_;

	protected:

		void Update(); // virtual
		

	public:

		static const Camera* GetDefaultCamera();

		static Camera* active_camera;


		Camera(const char* name = "camera");


		float fov;
		float aspect;
		float clip_near;
		float clip_far;

		glm::mat4 view;
		glm::mat4 projection;

	};

};