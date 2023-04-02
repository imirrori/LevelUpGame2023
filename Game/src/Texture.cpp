//
// Created by Dmitry Morozov on 29/3/23.
//

#include "Texture.hpp"
#include "GL/glew.h"

#include "lib/STBI/stbi_image.h"

#include <array>

std::unordered_map<std::string, Texture> Texture::Textures_;

void Texture::LoadTexture(const std::string &name, const std::string &file, bool isAlpha) {
  Texture texture{};

  if (isAlpha) {
	texture.image_format = GL_RGBA;
	texture.internal_format = GL_RGBA;
  }

  int width;
  int height;
  int channels;

  stbi_set_flip_vertically_on_load(true);

  auto data = stbi_load(file.c_str(), &width, &height, &channels, 0);

  if (data) {
	texture.Generate(width, height, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	Texture::Textures_[name] = texture;
	stbi_image_free(data);
  } else {
	std::cerr << "Load Texture Error ! :  " << stbi_failure_reason() << std::endl;
  }

}

Texture::TexturePtr Texture::GetTexture(const std::string &name) {
  try {

	if (Texture::Textures_.at(name).m_Id==0) {
	  std::cerr << "Texture " << name << " not found" << std::endl;
	  throw std::runtime_error("Texture not found");
	}
  } catch (std::exception &e) {
	std::cerr << e.what() << std::endl;

  }
  return std::make_shared<Texture>(Texture::Textures_.at(name));
}

void Texture::Generate(unsigned int width_, unsigned int height_, auto data) {

  glGenTextures(1, &m_Id);

  this->wrap_s = GL_REPEAT;
  this->wrap_t = GL_REPEAT;
  this->filter_min = GL_LINEAR;
  this->filter_max = GL_LINEAR;

  this->width = width_;
  this->height = height_;

  glBindTexture(GL_TEXTURE_2D, m_Id);
  glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, image_format, GL_UNSIGNED_BYTE, data);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<GLint>(this->wrap_s));
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<GLint>(this->wrap_t));
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(this->filter_min));
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(this->filter_max));

  glBindTexture(GL_TEXTURE_2D, 0);

}

void Texture::Bind(unsigned int slot) const {

  glActiveTexture(GL_TEXTURE0 + slot);
  glBindTexture(GL_TEXTURE_2D, m_Id);

}