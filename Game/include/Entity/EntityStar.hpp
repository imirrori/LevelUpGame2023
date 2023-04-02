//
// Created by Dmitry Morozov on 25/3/23.
//

#ifndef LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITYSTAR_HPP_
#define LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITYSTAR_HPP_

#include "GL/glew.h"

#include "Entity.hpp"

class EntityStar : public Entity {
 public:

  EntityStar(b2World &world, glm::vec2 coord, glm::vec2 size) : Entity(world, coord, size) { Init(); }

  ~EntityStar() override = default;

  void onUpdate(float delta) override;
  void onRender() override;
  void onCollision(std::shared_ptr<IEntity> collision_entity) override;

 private:
  void Init();

};

#endif //LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITYSTAR_HPP_
