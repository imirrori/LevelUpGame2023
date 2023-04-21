//
// Created by Dmitry Morozov on 22/4/23.
//

#ifndef MARIO_GAME_SRC_SPRITE_HPP_
#define MARIO_GAME_SRC_SPRITE_HPP_

#include <GL/gl.h>

class Sprite {

 public:

  struct Point {
	GLfloat x;
	GLfloat y;
  };

  struct Size {

	GLfloat width;
	GLfloat height;

  };

  struct Rect {

	GLfloat top;
	GLfloat bottom;
	GLfloat left;
	GLfloat right;

  };

 public:

  explicit Sprite(unsigned int m_pNumberOfTextures);
  ~Sprite();

  void onUpdate(float delta);
  void onRender();

  bool AddTexture(const char *p_fileName, bool p_useTransparency = true);

  void SetPosition(GLfloat p_x, GLfloat p_y);
  void SetPosition(Point p_position);

  Point GetPosition();
  [[nodiscard]] Size GetSize() const;

  void SetFrameSize(GLfloat p_width, GLfloat p_height);
  void SetVelocity(GLfloat p_velocity);
  void SetNumberOfFrames(unsigned int p_frames);

  [[nodiscard]] bool isCollideable() const;
  void IsCollideable(bool p_value);
  void FlipHorizontal(bool p_value);
  void FlipVertical(bool p_value);
  void IsActive(bool p_value);
  [[nodiscard]] bool IsActive() const;
  void IsVisible(bool p_value);
  [[nodiscard]] bool IsVisible() const;
  void UseTransparency(bool p_value);
 protected:

  GLuint *m_textures;

  unsigned int m_textureIndex;
  unsigned int m_currentFrame;
  unsigned int m_numberOfFrames;
  GLfloat m_animationDelay;
  GLfloat m_animationElapsed;

  Point m_position;
  Size m_size;
  GLfloat m_velocity;

  bool m_isCollideable;
  bool m_flipHorizontal;
  bool m_flipVertical;
  bool m_isVisible;
  bool m_isActive;
  bool m_useTransparency;
  bool m_isSpriteSheet;

  GLuint GetCurrentFrame();

};

#endif //MARIO_GAME_SRC_SPRITE_HPP_
