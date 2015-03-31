#include <ProjectBlah.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb\stb_image.h>

#include <aie\gl_core_4_4.h>
#include <glfw\glfw3.h>


#include <pb\TextureManager.h>


using namespace std;

namespace pb
{
	TextureManager* TextureManager::texture_manager_instance_ = nullptr;
	map<string, TextureManager::shared_texture_data> TextureManager::shared_texture_data_map = map<string, TextureManager::shared_texture_data>();

	TextureManager::TextureManager()
	{
		load_new_texture("./data/texture/default_texture.png");
		//load_new_texture();
	}

	TextureManager::~TextureManager()
	{
		/// @todo clean up gpu and cpu memory
		/// glDeleteTextures
	}



	int TextureManager::GetTextureWidth(const string& texture_path)
	{
		if (shared_texture_data_map.find(texture_path) == shared_texture_data_map.end())
			load_new_texture(texture_path);

		return shared_texture_data_map[texture_path].width;
	}

	int TextureManager::GetTextureHeight(const string& texture_path)
	{
		if (shared_texture_data_map.find(texture_path) == shared_texture_data_map.end())
			load_new_texture(texture_path);

		return shared_texture_data_map[texture_path].height;
	}

	unsigned int TextureManager::GetTextureId(const string& texture_path)
	{
		if (shared_texture_data_map.find(texture_path) == shared_texture_data_map.end())
			load_new_texture(texture_path);

		return shared_texture_data_map[texture_path].texture_id;
	}




	void TextureManager::load_new_texture(string texture_path)
	{
		shared_texture_data data;

		unsigned char* image_source = stbi_load(texture_path.c_str(), &data.width, &data.height, &data.format, STBI_default);

		if (image_source == nullptr)
		{
			image_source = new unsigned char[3]{100, 200, 120};
			data.width = 1; data.height = 1;
		}

		glGenTextures(1, &data.texture_id);
		glBindTexture(GL_TEXTURE_2D, data.texture_id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, data.width, data.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_source);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		stbi_image_free(image_source);

		shared_texture_data_map[texture_path] = data;
	}

}