#pragma once

#include <GLFW/glfw3.h>

namespace Textures {
class Texture {
public:

  Texture();
  explicit Texture(const char *fileName);

  GLuint getId() const;

private:

  GLuint textureID_;
  unsigned char *data_;
};
}
