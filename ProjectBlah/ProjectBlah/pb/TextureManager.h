
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


	public:

		struct texture_data
		{
			std::string path;
			unsigned int location;
			unsigned int id;
			int width;
			int height;
			int format;
		};


		/// @todo Create a means of unloading textures (maybe grab and drop system).

		/// @brief Gets id for texture.
		/// @note Loads texture if not already loaded.
		const texture_data& GetTextureData(std::string texture_path = "");



	private:

		std::map<std::string, texture_data>loaded_textures_;


		void load_new_texture(std::string texture_path = "");

	};


}