//
// Created by Dmitry Morozov on 22/4/23.
//

#include "Sprite.hpp"

Sprite::Sprite(const unsigned int p_numberOfTextures) {

  m_textures = new GLuint[p_numberOfTextures];
  m_textureIndex = 0;
  m_currentFrame = 0;
  m_numberOfFrames = 0;
  m_animationDelay = 0.25f;
  m_animationElapsed = 0.0f;
  m_position.x = 0.0f;
  m_position.y = 0.0f;
  m_size.height = 0.0f;
  m_size.width = 0.0f;
  m_velocity = 0.0f;

  m_isCollideable = true;
  m_flipHorizontal = false;
  m_flipVertical = false;
  m_isVisible = false;
  m_isActive = false;
  m_isSpriteSheet = false;

}

void Sprite::onUpdate(const float delta) {

}

void Sprite::onRender() {

}

bool Sprite::AddTexture(const char *p_fileName, const bool p_useTransparency) {
  return 0;
}

GLuint Sprite::GetCurrentFrame() {

  if (m_isSpriteSheet) {

	return m_textures[0];

  } else {

	return m_textures[m_currentFrame];

  }

}

void Sprite::SetPosition(const GLfloat p_x, const GLfloat p_y) {

  m_position.x = p_x;
  m_position.y = p_y;

}

void Sprite::SetPosition(const Point p_position) { m_position = p_position; }

Sprite::Point Sprite::GetPosition() { return m_position; }

Sprite::Size Sprite::GetSize() const { return m_size; }

void Sprite::SetFrameSize(const GLfloat p_width, const GLfloat p_height) {

  m_size.width = p_width;
  m_size.height = p_height;

}

void Sprite::SetVelocity(const GLfloat p_velocity) { m_velocity = p_velocity; }

void Sprite::SetNumberOfFrames(const unsigned int p_frames) { m_numberOfFrames = p_frames; }

bool Sprite::isCollideable() const { return m_isCollideable; }

void Sprite::IsCollideable(const bool p_value) { m_isCollideable = p_value; }

void Sprite::FlipHorizontal(const bool p_value) { m_flipHorizontal = p_value; }

void Sprite::FlipVertical(const bool p_value) { m_flipVertical = p_value; }

void Sprite::IsActive(const bool p_value) { m_isActive = p_value; }

bool Sprite::IsActive() const { return m_isActive; }

void Sprite::IsVisible(const bool p_value) { m_isVisible = p_value; }

bool Sprite::IsVisible() const { return m_isVisible; }

void Sprite::UseTransparency(const bool p_value) { m_useTransparency = p_value; }

Sprite::~Sprite() {

  delete[] m_textures;

}
