//
// Created by Dmitry Morozov on 24/3/23.
//

#ifndef LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITY_HPP_
#define LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITY_HPP_

#include "box2d/box2d.h"
#include "GL/glew.h"
#include "glm/vec2.hpp"

#include "interface/IEntity.hpp"

#include <memory>
#include <string>

class Entity : public IEntity {
 public:

  ~Entity() override = default;

  [[nodiscard]] std::string GetTag() const override { return vTag; };
  void SetTag(std::string &tag) override { vTag = tag; };

  [[nodiscard]] glm::vec2 GetPosition() const override { return vPosition; };
  [[nodiscard]] float GetRotation() const override { return vRotation; };
  [[nodiscard]] glm::vec2 GetScale() const override { return vScale; };

  void onUpdate(float delta) override {};
  void onRender() override {};
  void onCollision(std::shared_ptr<IEntity> collision_entity) override {};

 protected:

  static constexpr float pixelToM_ = 150.f;

  std::string vTag = "default";

  glm::vec2 vPosition = glm::vec2(0.0f, 0.0f);
  float vRotation = 0.0f;
  glm::vec2 vScale = glm::vec2(1.0f, 1.0f);

};


#endif //LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITY_HPP_
