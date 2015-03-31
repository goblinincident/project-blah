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



	const TextureManager::texture_data& TextureManager::GetTextureData(string texture_path)
	{

		if (loaded_textures_.find(texture_path) == loaded_textures_.end())
			load_new_texture(texture_path);

		return loaded_textures_[texture_path];
	}




	void TextureManager::load_new_texture(string texture_path)
	{
		texture_data data;

		unsigned char* image_source = stbi_load(texture_path.c_str(), &data.width, &data.height, &data.format, STBI_default);

		if (image_source == nullptr)
		{
			image_source = new unsigned char[3]{255, 255, 255};
			data.width = 1; data.height = 1;
		}

		glGenTextures(1, &data.id);
		glBindTexture(GL_TEXTURE_2D, data.id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, data.width, data.height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_source);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		stbi_image_free(image_source);

		loaded_textures_[texture_path] = data;
	}

}