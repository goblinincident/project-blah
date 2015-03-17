#pragma once

#include <glm\glm.hpp>

namespace pb
{

	/** @brief Stores available vertex data thats extracted from
	* a mesh, and provides a default value if it's required by a
	* material and not found.
	**/
	class VertexObjectData
	{
		glm::vec3* position_;
		glm::vec4* colour_;
		glm::vec3* normal_;
		glm::vec2* uv_;
		glm::vec3* bi_normal_;
		glm::vec3* tangent_;

	public:

		/** @brief Provide values extracted from mesh data.
		* If not available use 'nullptr'.
		**/
		VertexObjectData(
			glm::vec3* position = nullptr,
			glm::vec4* colour = nullptr,
			glm::vec3* normal = nullptr,
			glm::vec2* uv = nullptr,
			glm::vec3* bi_normal = nullptr,
			glm::vec3* tangent = nullptr);

		glm::vec3 GetPosition() const;
		glm::vec4 GetColour() const;
		glm::vec3 GetNormal() const;
		glm::vec2 GetUv() const;
		glm::vec3 GetBiNormal() const;
		glm::vec3 GetTangent() const;

	};

};