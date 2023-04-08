//
// Created by Dmitry Morozov on 24/3/23.
//

#ifndef LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_INCLUDE_IENTITY_HPP_
#define LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_INCLUDE_IENTITY_HPP_

#include "GL/glew.h"

#include <glm/vec2.hpp>
#include <string>
#include <memory>

class IEntity {
 public:
  virtual ~IEntity() = default;

  virtual void onUpdate(float delta) = 0;
  virtual void onRender() = 0;
  virtual void onCollision(IEntity * collision_entity) = 0;

  [[nodiscard]] virtual std::string GetTag() const = 0;
  [[nodiscard]] virtual glm::vec2 GetPosition() const = 0;
  [[nodiscard]] virtual float GetRotation() const = 0;
  [[nodiscard]] virtual glm::vec2 GetScale() const = 0;

  virtual void SetTag(std::string &tag) = 0;

};

#endif //LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_INCLUDE_IENTITY_HPP_
