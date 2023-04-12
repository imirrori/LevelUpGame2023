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

/**
 * @brief Base class for all entities
 * @details
 * - Entity is a base class for all entities in the game
 */
class Entity : public IEntity {
 public:

  /**
   * @brief Default destructor
   */
  ~Entity() override = default;

  /**
   * @brief Get tag of the entity
   * @return Tag of the entity
   */
  [[nodiscard]] std::string GetTag() const override { return vTag; };

  /**
   * @brief Set tag of the entity
   * @param tag Tag of the entity
   */
  void SetTag(std::string &tag) override { vTag = tag; };


  /**
   * @brief Get position of the entity
   * @return Position of the entity
   */
  [[nodiscard]] glm::vec2 GetPosition() const override { return vPosition; };

  /**
   * @brief Get rotation of the entity
   * @return Rotation of the entity
   */
  [[nodiscard]] float GetRotation() const override { return vRotation; };

  /**
   * @brief Get scale of the entity
   * @return Scale of the entity
   */
  [[nodiscard]] glm::vec2 GetScale() const override { return vScale; };

  /**
   * @brief Update entity
   * @param delta Delta time
   */
  void onUpdate(float delta) override {};

  /**
   * @brief Render entity
   */
  void onRender() override {};

  /**
   * @brief Handle collision with other entity
   * @param collision_entity Entity with which collision occurred
   */
  void onCollision(IEntity * collision_entity) override {};

 protected:


  static constexpr float pixelToM_ = 150.f; /// Mario pixel size

  std::string vTag = "default";

  glm::vec2 vPosition = glm::vec2(0.0f, 0.0f); /// Position of the entity
  float vRotation = 0.0f; /// Rotation of the entity
  glm::vec2 vScale = glm::vec2(1.0f, 1.0f); /// Scale of the entity

};


#endif //LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITY_HPP_
