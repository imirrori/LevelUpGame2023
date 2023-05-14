#pragma once


namespace Textures {
	class ITexture {
	public:
		typedef void (*TTexProc)(unsigned char* data, int wigth, int height, int cnt);


		static void LoadTexture(const char* fileName, GLuint* textureID, int wrap, int filter, TTexProc proc);
	};

}