//
// Created by Dmitry Morozov on 25/3/23.
//

#ifndef LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITYMUSHROOM_HPP_
#define LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITYMUSHROOM_HPP_

#include "Entity.hpp"

class EntityMushroom : public Entity {
 public:

  EntityMushroom(glm::vec2 coord, glm::vec2 size) : Entity(coord, size) {
	Init();
  }

  ~EntityMushroom() override = default;

  void onUpdate() override;
  void onRender() override;
  void onCollision() override;

 private:
  void Init();

};

#endif //LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITYMUSHROOM_HPP_
