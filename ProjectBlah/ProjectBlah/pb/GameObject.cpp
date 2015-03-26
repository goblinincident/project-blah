
#include <assert.h>
#include <string>
#include <ant\AntTweakBar.h>
#include <aie\Gizmos.h>

#include <pb\GameObject.h>
#include <pb\Window.h>

#include <glm\ext.hpp>

using namespace glm;

namespace pb
{
	GameObject* GameObject::root_node_ = nullptr;
	std::list<GameObject*> GameObject::all_game_objects = std::list<GameObject*>();


	void GameObject::UpdateAllGameObjects(GameObject* go)
	{
		if (go != GameObject::root_node_)
		{
			go->UpdateTransform();
			go->DrawTransform();
			go->Update(); // virtual
		}

		for (auto chld_it = go->children.begin(); chld_it != go->children.end(); chld_it++)
			UpdateAllGameObjects(*chld_it);
	}


	GameObject::GameObject(const char* name) :
		name(name),
		parent(nullptr),
		position_local(vec3(0)),
		rotation_local(vec3(0)),
		scale_local(vec3(1, 1, 1)),
		transform_matrix_local(mat4()),
		transform_matrix_world(mat4()),
		position_matrix_local(mat4()),
		rotation_matix_local(mat4()),
		scale_matrix_local(mat4())
	{
		if (root_node_ == nullptr)
			root_node_ = this;
		else
			AttachParent(root_node_);

		all_game_objects.push_back(this);
	}

	GameObject::~GameObject()
	{
		if (this == root_node_)
		{
			all_game_objects.clear();
			children.clear();
		}
		else
		{
			DetachParent();

			for (auto cld_it = children.begin(); cld_it != children.end(); cld_it++)
			{
				(*cld_it)->DetachParent();
			}

			all_game_objects.remove(this);
		}
	}



	void GameObject::AttachParent(GameObject* parent)
	{
		assert(this != root_node_ && "Attempted to give the root_node a parent!");

		if (this->parent != parent)
		{
			if (this->parent != nullptr)
				this->parent->DettachChild(this);

			this->parent = parent;

			parent->AttachChild(this);
		}

	}

	void GameObject::DetachParent()
	{
		assert(this != root_node_ && "Attempted to detach parent from root-node!");

		assert(parent != nullptr && "Don't know how this happened!");

		parent->DettachChild(this);

		parent = root_node_;
	}



	void GameObject::AttachChild(GameObject* child)
	{
		assert(child != this && "Attempted to add self as child!");

		if (std::find(children.begin(), children.end(), child) == children.end()) // not already child
		{
			children.push_back(child);

			if (child->parent != this)
			{
				child->DetachParent();

				child->AttachParent(this);
			}
		}
	}

	void GameObject::DettachChild(GameObject* child)
	{
		assert(std::find(children.begin(), children.end(), child) != children.end()
			&& "Attempted to detach child that's not contained in 'children_'!");


		children.remove(child);

		if (child->parent != this)
		{
			child->DetachParent();
		}
	}



	static void TW_CALL SetScaleCallback(const void* value, void* clientData)
	{
		static_cast<GameObject*>(clientData)->position_local.x = *static_cast<const float*>(value);
	}

	static void TW_CALL GetScaleCallback(void* value, void* clienntData)
	{
		*static_cast<float*>(value) = static_cast<GameObject*>(clienntData)->position_local.x;
	}

	void GameObject::OpenDebugWindow()
	{
		InititializeDebugWindow(name);

		
		// tewakable
		TwAddVarRW(bar, "draw tran?", TW_TYPE_BOOL32, &draw_transform_,
			"group='Game Object' "
			"help='Draws a transform gizmo.' ");

		TwAddVarRW(bar, "local_pos_x", TW_TYPE_FLOAT, &position_local.x, "label='x' group='position local'");
		TwAddVarRW(bar, "local_pos_y", TW_TYPE_FLOAT, &position_local.y, "label='y' group='position local'");
		TwAddVarRW(bar, "local_pos_z", TW_TYPE_FLOAT, &position_local.z, "label='z' group='position local'");
						 																		
		TwAddVarRW(bar, "local_rot_x", TW_TYPE_FLOAT, &rotation_local.x, "label='x' group='rotation local'");
		TwAddVarRW(bar, "local_rot_y", TW_TYPE_FLOAT, &rotation_local.y, "label='y' group='rotation local'");
		TwAddVarRW(bar, "local_rot_z", TW_TYPE_FLOAT, &rotation_local.z, "label='z' group='rotation local'");

		TwAddVarCB(bar, "scale_all", TW_TYPE_FLOAT, SetScaleCallback, GetScaleCallback, this, "");

		// readable
		TwAddVarRO(bar, "world_pos_x", TW_TYPE_FLOAT, &position_world.x, "label='x' group='position world'");
		TwAddVarRO(bar, "world_pos_y", TW_TYPE_FLOAT, &position_world.y, "label='y' group='position world'");
		TwAddVarRO(bar, "world_pos_z", TW_TYPE_FLOAT, &position_world.z, "label='z' group='position world'");

		TwAddVarRO(bar, "world_rot_x", TW_TYPE_FLOAT, &rotation_world.x, "label='x' group='rotation world'");
		TwAddVarRO(bar, "world_rot_y", TW_TYPE_FLOAT, &rotation_world.y, "label='y' group='rotation world'");
		TwAddVarRO(bar, "world_rot_z", TW_TYPE_FLOAT, &rotation_world.z, "label='z' group='rotation world'");

		// layout
		std::string layout = "'"; layout += name; layout += "'/'position world' group='Game Object'";
		TwDefine(layout.c_str());

		layout.clear();
		layout = "'"; layout += name; layout += "'/'rotation world' group='Game Object'";
		TwDefine(layout.c_str());

		layout.clear();
		layout = "'"; layout += name; layout += "'/'position local' group='Game Object'";
		TwDefine(layout.c_str());

		layout.clear();
		layout = "'"; layout += name; layout += "'/'rotation local' group='Game Object'";
		TwDefine(layout.c_str());
	}

	void GameObject::CloseDebugWindow()
	{
		TwDeleteBar(bar);
	}



	void GameObject::UpdateTransform()
	{
		/// @todo Currently updates everything, every frame. crazy unoptimized.

		// Update local matrix from local variables //-------------------//

		// Position //
		position_matrix_local[3][0] = position_local.x;
		position_matrix_local[3][1] = position_local.y;
		position_matrix_local[3][2] = position_local.z;

		vec3 rad_rot = radians(rotation_local);

		const float cr = cos(rad_rot.x);
		const float sr = sin(rad_rot.x);
		const float cp = cos(rad_rot.y);
		const float sp = sin(rad_rot.y);
		const float cy = cos(rad_rot.z);
		const float sy = sin(rad_rot.z);

		rotation_matix_local[0][0] = cp*cy;
		rotation_matix_local[0][1] = cp*sy;
		rotation_matix_local[0][2] = -sp;

		const float srsp = sr*sp;
		const float crsp = cr*sp;

		rotation_matix_local[1][0] = srsp*cy - cr*sy;
		rotation_matix_local[1][1] = srsp*sy + cr*cy;
		rotation_matix_local[1][2] = sr*cp;

		rotation_matix_local[2][0] = crsp*cy + sr*sy;
		rotation_matix_local[2][1] = crsp*sy - sr*cy;
		rotation_matix_local[2][2] = cr*cp;

		// Scale //
		scale_matrix_local[0][0] = scale_local.x;
		scale_matrix_local[1][1] = scale_local.y;
		scale_matrix_local[2][2] = scale_local.z;


		transform_matrix_local = position_matrix_local * rotation_matix_local * scale_matrix_local;



		// Update global matrix and extract global variables //-------------------//

		transform_matrix_world = parent->transform_matrix_world * transform_matrix_local;
		auto m = &transform_matrix_world;

		// Position //

		position_world.x = (*m)[3][0];
		position_world.y = (*m)[3][1];
		position_world.z = (*m)[3][2];


		// Scale //

		// zero check
		if ((*m)[0][1] == 0 &&
			(*m)[0][2] == 0 &&
			(*m)[1][0] == 0 &&
			(*m)[1][2] == 0 &&
			(*m)[2][0] == 0 &&
			(*m)[2][1] == 0)
		{
			scale_world.x = (*m)[0][0];
			scale_world.y = (*m)[1][1];
			scale_world.z = (*m)[2][2];
		}

		else
		{
			scale_world.x = sqrtf((*m)[0][0] * (*m)[0][0] + (*m)[0][1] * (*m)[0][1] + (*m)[0][2] * (*m)[0][2]);
			scale_world.y = sqrtf((*m)[1][0] * (*m)[1][0] + (*m)[1][1] * (*m)[1][1] + (*m)[1][2] * (*m)[1][2]);
			scale_world.z = sqrtf((*m)[2][0] * (*m)[2][0] + (*m)[2][1] * (*m)[2][1] + (*m)[2][2] * (*m)[2][2]);
		}


		// Rotation // 
		mat4 mat = transform_matrix_world;

		vec3 scale_inv(1 / scale_world.x, 1 / scale_world.y, 1 / scale_world.z);

		float desired_y = -asinf(mat[0][2] * scale_inv.x);
		float cos_y = cosf(desired_y);

		desired_y = degrees(desired_y);


		float rot_x, rot_y, desired_x, desired_z;

		// zero check
		if (cos_y == 0)
		{
			desired_x = 0.0;
			rot_x = mat[1][1] * scale_inv.y;
			rot_y = -mat[1][0] * scale_inv.y;

			desired_z = degrees(atan2(rot_y, rot_x));
		}

		else
		{
			float invC = 1 / cos_y;
			rot_x = mat[2][2] * invC * scale_inv.z;
			rot_y = mat[1][2] * invC * scale_inv.y;
			desired_x = degrees(atan2(rot_y, rot_x));
			rot_x = mat[0][0] * invC * scale_inv.x;
			rot_y = mat[0][1] * invC * scale_inv.x;
			desired_z = degrees(atan2(rot_y, rot_x));
		}

		// negative fix
		if (desired_x < 0.0) desired_x += 360.0;
		if (desired_y < 0.0) desired_y += 360.0;
		if (desired_z < 0.0) desired_z += 360.0;

		rotation_world.x = desired_x;
		rotation_world.y = desired_y;
		rotation_world.z = desired_z;
	}

	void GameObject::DrawTransform()
	{
		if (draw_transform_)
			Gizmos::addTransform(transform_matrix_world);
	}


};