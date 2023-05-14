#include <windows.h>
#include <gl/gl.h>

#include<stb_image.h>

#include"Texture.hpp"

namespace Textures {
	void Texture::LoadTexture(const char* fileName, GLuint* textureID, int wrap, int filter, TTexProc proc) {
		int wigth, height, cnt;

		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(fileName, &wigth, &height, &cnt, 0);

		if (!data)
		{
			printf("%s \"%s\" %s\n", "File", fileName, "not found.");
		}
		if (proc)
		{
			proc(data, wigth, height, cnt);
		}


		glGenTextures(1, textureID);
		glBindTexture(GL_TEXTURE_2D, *textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, wigth, height,
			0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(data);

	}
}


