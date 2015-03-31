
#pragma once

#include <string>
#include <map>
#include <pb\Renderable.h>

class ProjectBlah;


namespace pb
{
	class TextureManager
	{
		friend class ProjectBlah;

		static TextureManager* texture_manager_instance_;
		TextureManager();
		~TextureManager();

		struct shared_texture_data
		{
			int width;
			int height;
			int format;
			unsigned int texture_id;
		};

	public:


		/// @todo Create a means of unloading textures (maybe grab and drop system).

		/// @brief Gets id for texture.
		/// @note Loads texture if not already loaded.
		//const Renderable::texture_data GetTextureData(std::string texture_path = "");

		static int GetTextureWidth(const std::string& texture_path);
		static int GetTextureHeight(const std::string& texture_path);
		static unsigned int GetTextureId(const std::string& texture_path);


	private:

		static std::map<std::string, shared_texture_data>shared_texture_data_map;


		static void load_new_texture(std::string texture_path = "");

	};


}