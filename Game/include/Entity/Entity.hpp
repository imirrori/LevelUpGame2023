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
  void SetTag(std::string &tag) override { vTag = tag; };
  [[nodiscard]] glm::vec2 GetPosition() const override { return vPosition; };
  [[nodiscard]] float GetRotation() const override { return vRotation; };
  [[nodiscard]] glm::vec2 GetScale() const override { return vScale; };

  [[nodiscard]] glm::vec2 GetCoord() const { return coord_; };
  [[nodiscard]] glm::vec2 GetSize() const { return size_; };
  [[nodiscard]] float pixel_to_m() const { return pixelToM_; }

  std::shared_ptr<Entity> GetEventHandler() { return std::make_shared<Entity>(*this); }

 protected:
  glm::vec2 coord_;
  glm::vec2 size_;
  float pixelToM_;

  std::string vTag = "default";
  glm::vec2 vPosition;
  float vRotation = 0.0f;
  glm::vec2 vScale;

};

#endif //LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITY_HPP_
