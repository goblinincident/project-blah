
#include <aie\Gizmos.h>

#include <pb\Grid.h>

using namespace glm;

namespace pb
{

	Grid::Grid(const char* name) : GameObject(name),
		size_(10),
		spacing_(1)
	{}

	void Grid::Update()
	{
		const vec4 black = vec4(0, 0, 0, 1);
		const vec4 white = vec4(1, 1, 1, 1);



		for (int i = 0; i < (size_ * 2) + 1; ++i)
		{

			vec4 l_s = vec4(-size_ + i, 0, size_, 1);
			vec4 l_e = vec4(-size_ + i, 0, -size_, 1);

			l_s = transform_matrix_world * l_s;
			l_e = transform_matrix_world * l_e;

			Gizmos::addLine(
				//vec3(-size_ + i, 0, size_) + position_world,
				//vec3(-size_ + i, 0, -size_) + position_world,
				vec3(l_s.x, l_s.y, l_s.z), vec3(l_e.x, l_e.y, l_e.z),
				i == size_ ? *(vec4*)&white : *(vec4*)&black);

			Gizmos::addLine(
				vec3(size_, 0, -size_ + i),// + position_world,
				vec3(-size_, 0, -size_ + i),// + position_world,
				i == size_ ? *(vec4*)&white : *(vec4*)&black);
		}
	}
};