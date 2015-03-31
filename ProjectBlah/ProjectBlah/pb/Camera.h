


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
		static Camera* active_camera_;

		float fov_;
		float aspect_;
		float clip_near_;
		float clip_far_;

		glm::mat4 view_;
		glm::mat4 projection_;

	protected:

		void Update(); // virtual override
		

	public:

		static const Camera* GetDefaultCamera();
		static const Camera* GetActiveCamera();

		const float GetFov() const;
		const float GetAspect() const;
		const float GetClipNear() const;
		const float GetClipFar() const;
		const glm::mat4& GetView() const;
		const glm::mat4& GetProjection() const;

		Camera(const char* name = "camera");






	};

};