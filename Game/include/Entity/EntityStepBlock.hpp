//
// Created by Dmitry Morozov on 7/4/23.
//

#ifndef MARIO_GAME_SRC_ENTITY_ENTITYSTEPBLOCK_HPP_
#define MARIO_GAME_SRC_ENTITY_ENTITYSTEPBLOCK_HPP_

#include "Entity/Entity.hpp"
#include "EventSystem.hpp"
#include "Texture.hpp"

class EntityStepBlock : public Entity {
 public:
  EntityStepBlock(EventSystem &event_handler_, b2World &world, glm::vec2 position, glm::vec2 scale);
  ~EntityStepBlock() override;

  void onUpdate(float delta) override;
  void onRender() override;
  void onCollision(IEntity *collision_entity) override;

 private:
  Texture *texture;

  b2Body *mp_Body;

};

#endif //MARIO_GAME_SRC_ENTITY_ENTITYSTEPBLOCK_HPP_
