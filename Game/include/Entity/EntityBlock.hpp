//
// Created by Dmitry Morozov on 25/3/23.
//

#ifndef LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITYBLOCK_HPP_
#define LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITYBLOCK_HPP_

#include "box2d/box2d.h"
#include "GL/glew.h"
#include "glm/vec2.hpp"

#include "Entity.hpp"
#include "EventSystem.hpp"
#include "Texture.hpp"

/**
 * @brief Block entity
 * @details
 * - Block entity is a block (brick) entity in the game
 */
class EntityBlock : public Entity {
 public:

  /**
   * @brief Construct a new Entity Block object
   *
   * @param event_handler_
   * @param world_
   * @param position
   * @param scale
   */
  EntityBlock(EventSystem &event_handler_, b2World &world, glm::vec2 position, glm::vec2 scale);

  /**
   * @brief Default destructor
   */
  ~EntityBlock() override = default;

  /**
   * @brief Get tag of the block entity
   * @return Tag of the entity
   */
  [[nodiscard]] std::string GetTag() const override { return vTag; };

  /**
   * @brief Update block entity
   * @param delta  Time between frames
   */
  void onUpdate(float delta) override;

  /**
   * @brief Render block entity
   */
  void onRender() override;

  /**
   * @brief Get position of the block entity
   * @return Position of the entity
   */
  [[nodiscard]] glm::vec2 GetPosition() const override { return vPosition; };

  /**
   * @brief Execute collision logic for block entity
   * @param collision_entity  Entity that collided with block entity
   */
  void onCollision(IEntity *collision_entity) override;

 private:
  const void Shake_(float delta);

  int hp_ = 3;

  Texture *current_texture;
  Texture *textures[3];

  b2Body *mp_Body;

};

#endif //LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITYBLOCK_HPP_
