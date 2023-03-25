//
// Created by Dmitry Morozov on 25/3/23.
//

#ifndef LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITYBLOCK_HPP_
#define LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITYBLOCK_HPP_

#include "Entity.hpp"
#include "glm/vec2.hpp"

class EntityBlock : public Entity {
 public:
  EntityBlock(glm::vec2 coord, glm::vec2 size) : Entity(coord, size) {
	Init();
  }

  ~EntityBlock() override = default;

  void onUpdate(double delta) override;
  void onRender() override;
  void onCollision(std::shared_ptr<IEntity> collision_entity) override;

 private:
  void Init();

};

#endif //LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITYBLOCK_HPP_
