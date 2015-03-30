
#pragma once

#include <string>
#include <map>

class ProjectBlah;


namespace pb
{
	class TextureManager
	{
		friend class ProjectBlah;

		static TextureManager* instance_;
		TextureManager();
		~TextureManager();

		std::map<std::string, unsigned int>loaded_textures_;

	public:

		/// @todo Create a means of unloading textures (maybe grab and drop system).

		/// @brief Gets id for texture.
		/// @note Loads texture if not already loaded.
		unsigned int GetTextureId(std::string texture_path);



	private:

		bool is_new_texture(std::string texture_path);
		void load_new_texture(std::string texture_path);

	};


}