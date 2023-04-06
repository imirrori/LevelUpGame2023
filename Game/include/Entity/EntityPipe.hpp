//
// Created by Dmitry Morozov on 25/3/23.
//

#ifndef LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITYPIPE_HPP_
#define LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITYPIPE_HPP_

#include "GL/glew.h"

#include "Entity.hpp"

class EntityPipe : public Entity {
 public:
  EntityPipe(b2World &world, glm::vec2 coord, glm::vec2 size) {

  }

  ~EntityPipe() override = default;

  void onUpdate(float delta) override;
  void onRender() override;
  void onCollision(std::shared_ptr<IEntity> collision_entity) override;

 private:

};

#endif //LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITYPIPE_HPP_
