//
// Created by Dmitry Morozov on 24/3/23.
//

#ifndef LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITY_HPP_
#define LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITY_HPP_

#include "IEntity.hpp"
#include "glm/vec2.hpp"

class Entity : public IEntity {
 public:
  Entity(glm::vec2 coord, glm::vec2 size) : coord_(coord), size_(size) {
  }

  ~Entity() override = default;

  void onInit() override;
  void onUpdate(double delta) override;
  void onRender() override;
  void onCollision(std::shared_ptr<IEntity> collision_entity) override;

  [[nodiscard]] glm::vec2 GetCoord() const { return coord_; };
  [[nodiscard]] glm::vec2 GetSize() const { return size_; };

 protected:
  glm::vec2 coord_;
  glm::vec2 size_;

};

#endif //LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITY_HPP_
