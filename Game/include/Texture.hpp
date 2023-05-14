#pragma once

#include <GLFW/glfw3.h>

namespace Textures {
class Texture {
public:

  using TTexProc = void (*)(unsigned char *data,
                            int            wigth,
                            int            height,
                            int            cnt);

  static void LoadTexture(const char *fileName,
                          GLuint     *textureID,
                          int         wrap,
                          int         filter,
                          TTexProc    proc);
};
}
