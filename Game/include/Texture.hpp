//
// Created by Dmitry Morozov on 29/3/23.
//

#ifndef LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_TEXTURE_HPP_
#define LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_TEXTURE_HPP_

#include "GL/glew.h"
#include "lib/STBI/stbi_image.h"

#include <iostream>
#include <string>
#include <unordered_map>

class Texture {
 public:
  Texture() = default;
  ~Texture() = default;

  //using TexturePtr = std::shared_ptr<Texture>;

  static void LoadTexture(const std::string &name, const std::string &file, bool isAlpha);
  static Texture &GetTexture(const std::string &name);

  void Generate(unsigned int width, unsigned int height, auto data);
  void Bind(unsigned int slot = 0) const;

  [[nodiscard]] inline unsigned int GetWidth() const { return width; }
  [[nodiscard]] inline unsigned int GetHeight() const { return height; }

 private:
  static std::unordered_map<std::string, Texture> Textures_;
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
