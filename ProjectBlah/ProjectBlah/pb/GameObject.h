

#pragma once
#include <string>
#include <list>
#include <glm\glm.hpp>

#include <pb\DebugWindow.h>

class ProjectBlah;

namespace pb
{
	/// @todo provide access restrictions on transform variables

	/// @brief Everything's a game object.
	class GameObject : public virtual DebugWindow
	{
		friend class ProjectBlah;

		static void UpdateAllGameObjects(GameObject* go);

		static GameObject* root_node_;


	protected:

		virtual void Update(){};


	public:

		static std::list<GameObject*> all_game_objects;


		GameObject* parent;

		std::list<GameObject*> children;

		std::string name;

		glm::vec3 position_local;
		glm::mat4 position_matrix_local;
		glm::vec3 rotation_local;
		glm::mat4 rotation_matix_local;
		glm::vec3 scale_local;
		glm::mat4 scale_matrix_local;

		glm::mat4 transform_matrix_local;

		glm::mat4 transform_matrix_world;

		glm::vec3 position_world;
		glm::mat4 position_matrix_world;
		glm::vec3 rotation_world;
		glm::mat4 rotation_matrix_world;
		glm::vec3 scale_world;
		glm::mat4 scale_matrix_world;


		GameObject(const char* name = "unnamed");

		

		~GameObject();


		void AttachParent(GameObject* parent);
		void DetachParent();
		void AttachChild(GameObject* child);
		void DettachChild(GameObject* child);


		void OpenDebugWindow(); // virtual
		void CloseDebugWindow(); // virtual

	private:

		GameObject(const GameObject&){}

		bool draw_transform_;

		void UpdateTransform();
		void DrawTransform();
	
	};

};