
#include <pb\VertexObjectData.h>

using namespace glm;

namespace pb
{

	VertexObjectData::VertexObjectData(vec3* position, vec4* colour, vec3* normal, vec2* uv, vec3* bi_normal, vec3* tangent) :
		position_(position), colour_(colour), normal_(normal), uv_(uv), bi_normal_(bi_normal), tangent_(tangent)
	{}

	glm::vec3 VertexObjectData::GetPosition() const
	{
		return position_ != nullptr ? *position_ : vec3();
	}

	glm::vec4 VertexObjectData::GetColour() const
	{
		return colour_ != nullptr ? *colour_ : vec4(1, 1, 1, 1);
	}

	glm::vec3 VertexObjectData::GetNormal() const
	{
		return normal_ != nullptr ? *normal_ : vec3(0, 0, 1);
	}

	glm::vec2 VertexObjectData::GetUv() const
	{
		return uv_ != nullptr ? *uv_ : vec2(0, 1);
	}

	glm::vec3 VertexObjectData::GetBiNormal() const
	{
		return bi_normal_ != nullptr ? *bi_normal_ : vec3(0, 1, 0);
	}

	glm::vec3 VertexObjectData::GetTangent() const
	{
		return bi_normal_ != nullptr ? *bi_normal_ : vec3(1, 0, 0);
	}

};