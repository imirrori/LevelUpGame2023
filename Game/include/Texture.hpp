#pragma once


#include"ITexture.h"

namespace Textures {
	class Texture
		:public ITexture {
	public:
		typedef void (*TTexProc)(unsigned char* data, int wigth, int height, int cnt);


		static void LoadTexture(const char* fileName, GLuint* textureID, int wrap, int filter, TTexProc proc);
	};


}