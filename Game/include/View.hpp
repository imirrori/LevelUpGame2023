//
// Created by Dmitry Morozov on 29/3/23.
//

#ifndef LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_VIEW_HPP_
#define LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_VIEW_HPP_

#include "GL/glew.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class View {
 public:

  View() {};
  View(float left, float right, float bottom, float top);

  inline void SetPosition(glm::vec2 position) {
	this->m_Position = position;
	RefreshVM_();
  }
  [[nodiscard]] inline const glm::vec2 &GetPosition() const { return this->m_Position; }

  [[nodiscard]] inline const glm::mat4 &GetViewMatrix() const { return this->m_ViewMatrix; }
  [[nodiscard]] inline const glm::mat4 &GetProjectionMatrix() const { return m_Projection; }

 private:
  void RefreshVM_();

 private:
  glm::vec2 m_Position;

  glm::mat4 m_ViewMatrix;
  glm::mat4 m_Projection;
};

#endif //LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_VIEW_HPP_
