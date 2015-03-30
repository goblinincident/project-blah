#include <ProjectBlah.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb\stb_image.h>

#include <aie\gl_core_4_4.h>
#include <glfw\glfw3.h>


#include <pb\TextureManager.h>


using namespace std;

namespace pb
{
	TextureManager* TextureManager::instance_ = nullptr;

	TextureManager::TextureManager()
	{
		load_new_texture("./data/texture/default_texture.png");
	}

	TextureManager::~TextureManager()
	{
		/// @todo clean up gpu and cpu memory
		/// glDeleteTextures
	}



	unsigned int TextureManager::GetTextureId(string texture_path)
	{

		if (is_new_texture(texture_path))
			load_new_texture(texture_path);

		return loaded_textures_[texture_path];
	}



	bool TextureManager::is_new_texture(string texture_path)
	{
		return loaded_textures_.find(texture_path) == loaded_textures_.end();
	}

	void TextureManager::load_new_texture(string texture_path)
	{
		int img_width = 0, img_height = 0, img_format = 0;
		unsigned char* data = stbi_load(texture_path.c_str(), &img_width, &img_height, &img_format, STBI_default);

		unsigned int tex_id = 0;

		glGenTextures(1, &tex_id);
		glBindTexture(GL_TEXTURE_2D, tex_id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img_width, img_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		stbi_image_free(data);

		loaded_textures_[texture_path] = tex_id;
	}

}