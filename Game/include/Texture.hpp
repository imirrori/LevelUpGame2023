//
// Created by Dmitry Morozov on 29/3/23.
//

#ifndef LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_TEXTURE_HPP_
#define LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_TEXTURE_HPP_

#include "GL/glew.h"
#include "STB/stb_image.h"

#include <iostream>
#include <string>
#include <unordered_map>

class Texture {
 public:
  static void LoadTexture(const std::string &name, const std::string &file, bool isAlpha);
  static Texture &GetTexture(const std::string &name);
 private:
  static std::unordered_map<std::string, Texture> Textures_;

 public:
  void Gernerate(unsigned int width, unsigned int height, unsigned char *data);
  void Bind(unsigned int slot = 0) const;
  inline unsigned int GetWidth() { return width; }
  inline unsigned int GetHeight() { return height; }

 private:
  unsigned int m_Id;
  unsigned int width, height;
  unsigned int internal_format;
  unsigned int image_format;
  unsigned int wrap_s;
  unsigned int wrap_t;
  unsigned int filter_min;
  unsigned int filter_max;
};

#endif //LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_TEXTURE_HPP_
