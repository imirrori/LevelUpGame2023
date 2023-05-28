#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Texture.hpp"

namespace Textures {
Texture::Texture()
  : textureID_{0}
{}

Texture::Texture(const char *fileName)
{
  int wigth, height, cnt;

  stbi_set_flip_vertically_on_load(true);
  data_ = stbi_load(fileName, &wigth, &height, &cnt, 0);

  if (!data_)
  {
    return;
  }

  glGenTextures(1, &textureID_);
  glBindTexture(GL_TEXTURE_2D, textureID_);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, wigth, height,
               0, GL_RGBA, GL_UNSIGNED_BYTE, data_);
  glBindTexture(GL_TEXTURE_2D, 0);
  stbi_image_free(data_);
}

GLuint Texture::getId() const
{
  return textureID_;
}
}
