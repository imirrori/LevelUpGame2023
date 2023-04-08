//
// Created by Dmitry Morozov on 7/4/23.
//

#ifndef MARIO_GAME_SRC_ENTITY_ENTITYCOINBLOCK_HPP_
#define MARIO_GAME_SRC_ENTITY_ENTITYCOINBLOCK_HPP_

#include "Entity/Entity.hpp"
#include "Entity/EntityCoin.hpp"

#include "EventSystem.hpp"
#include "glm/vec2.hpp"
#include "Texture.hpp"

#include "box2d/box2d.h"

class EntityCoinBlock : public Entity {
 public:
  EntityCoinBlock(EventSystem &event_handler, b2World &world, glm::vec2 position, glm::vec2 scale);
  ~EntityCoinBlock() override;

  void onUpdate(float delta) override;
  void onRender() override;
  void onCollision(IEntity *collision_entity) override;

 private:
  EntityCoin *coin_;

  Texture *current_texture;
  Texture *idle_texture;
  Texture *break_texture;

  b2Body *mp_Body;
};

#endif //MARIO_GAME_SRC_ENTITY_ENTITYCOINBLOCK_HPP_
