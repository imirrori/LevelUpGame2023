//
// Created by Dmitry Morozov on 24/3/23.
//

#ifndef LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITY_HPP_
#define LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITY_HPP_

#include "IEntity.hpp"
#include "glm/vec2.hpp"

#include <memory>
#include <string>

class Entity : public IEntity {
 public:

  ~Entity() override = default;

  void onInit() override;
  void onUpdate(float delta) override;
  void onRender() override;
  void onCollision(std::shared_ptr<IEntity> collision_entity) override;

  [[nodiscard]] std::string GetTag() const override { return vTag; };
  [[nodiscard]] glm::vec2 GetPosition() const override { return vPosition; };
  [[nodiscard]] float GetRotation() const override { return vRotation; };
  [[nodiscard]] glm::vec2 GetScale() const override { return vScale; };

  [[nodiscard]] glm::vec2 GetCoord() const { return coord_; };
  [[nodiscard]] glm::vec2 GetSize() const { return size_; };


  std::shared_ptr<IEntity> GetEventHandler() override { return std::make_shared<Entity>(*this); };

 protected:
  glm::vec2 coord_;
  glm::vec2 size_;

  std::string vTag = "default";
  glm::vec2 vPosition;
  float vRotation = 0.0f;
  glm::vec2 vScale;

};

#endif //LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITY_HPP_
