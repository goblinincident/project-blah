
#include <aie\Gizmos.h>
#include <glm\glm.hpp>


#include <pb\Dummy.h>

using namespace glm;

namespace pb
{

	Dummy::Dummy(const char* name) : GameObject(name)
	{}

	void Dummy::Update()
	{

		const vec4 red = vec4(1, 0, 0, 1);

		const vec4 cnr_front_face_tl = vec4(-.5f, .5f, .5f, 1);
		const vec4 cnr_front_face_tr = vec4(.5f, .5f, .5f, 1);
		const vec4 cnr_front_face_bl = vec4(-.5f, -.5f, .5f, 1);
		const vec4 cnr_front_face_br = vec4(.5f, -.5f, .5f, 1);

		const vec4 cnr_back_face_tl = vec4(-.5f, .5f, -.5f, 1);
		const vec4 cnr_back_face_tr = vec4(.5f, .5f, -.5f, 1);
		const vec4 cnr_back_face_bl = vec4(-.5f, -.5f, -.5f, 1);
		const vec4 cnr_back_face_br = vec4(.5f, -.5f, -.5f, 1);


		vec4 cnr_f_f_tl = transform_matrix_world * cnr_front_face_tl;
		vec4 cnr_f_f_tr = transform_matrix_world * cnr_front_face_tr;
		vec4 cnr_f_f_bl = transform_matrix_world * cnr_front_face_bl;
		vec4 cnr_f_f_br = transform_matrix_world * cnr_front_face_br;

		vec4 cnr_b_f_tl = transform_matrix_world * cnr_back_face_tl;
		vec4 cnr_b_f_tr = transform_matrix_world * cnr_back_face_tr;
		vec4 cnr_b_f_bl = transform_matrix_world * cnr_back_face_bl;
		vec4 cnr_b_f_br = transform_matrix_world * cnr_back_face_br;


		vec3 cnr_f_f_tl_v = vec3( cnr_f_f_tl.x, cnr_f_f_tl.y, cnr_f_f_tl.z );
		vec3 cnr_f_f_tr_v = vec3( cnr_f_f_tr.x, cnr_f_f_tr.y, cnr_f_f_tr.z );
		vec3 cnr_f_f_bl_v = vec3( cnr_f_f_bl.x, cnr_f_f_bl.y, cnr_f_f_bl.z );
		vec3 cnr_f_f_br_v = vec3( cnr_f_f_br.x, cnr_f_f_br.y, cnr_f_f_br.z );
		vec3 cnr_b_f_tl_v = vec3( cnr_b_f_tl.x, cnr_b_f_tl.y, cnr_b_f_tl.z );
		vec3 cnr_b_f_tr_v = vec3( cnr_b_f_tr.x, cnr_b_f_tr.y, cnr_b_f_tr.z );
		vec3 cnr_b_f_bl_v = vec3( cnr_b_f_bl.x, cnr_b_f_bl.y, cnr_b_f_bl.z );
		vec3 cnr_b_f_br_v = vec3( cnr_b_f_br.x, cnr_b_f_br.y, cnr_b_f_br.z );

		
		

		//// front face
		Gizmos::addLine(cnr_f_f_tl_v, cnr_f_f_tr_v, red);
		Gizmos::addLine(cnr_f_f_tr_v, cnr_f_f_br_v, red);
		Gizmos::addLine(cnr_f_f_br_v, cnr_f_f_bl_v, red);
		Gizmos::addLine(cnr_f_f_bl_v, cnr_f_f_tl_v, red);

		// back face
		Gizmos::addLine(cnr_b_f_tl_v, cnr_b_f_tr_v, red);
		Gizmos::addLine(cnr_b_f_tr_v, cnr_b_f_br_v, red);
		Gizmos::addLine(cnr_b_f_br_v, cnr_b_f_bl_v, red);
		Gizmos::addLine(cnr_b_f_bl_v, cnr_b_f_tl_v, red);

		//// connecting lines
		Gizmos::addLine(cnr_b_f_tl_v, cnr_f_f_tl_v, red);
		Gizmos::addLine(cnr_b_f_tr_v, cnr_f_f_tr_v, red);
		Gizmos::addLine(cnr_b_f_br_v, cnr_f_f_br_v, red);
		Gizmos::addLine(cnr_b_f_bl_v, cnr_f_f_bl_v, red);

	}

};