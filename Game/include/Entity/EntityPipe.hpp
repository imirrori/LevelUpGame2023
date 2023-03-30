//
// Created by Dmitry Morozov on 25/3/23.
//

#ifndef LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITYPIPE_HPP_
#define LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITYPIPE_HPP_

#include "Entity.hpp"

class EntityPipe : public Entity {
 public:
  EntityPipe(glm::vec2 coord, glm::vec2 size) : Entity(coord, size) {
	Init();
  }

  ~EntityPipe() override = default;

  void onInit() override;
  void onUpdate(float delta) override;
  void onRender() override;
  void onCollision(std::shared_ptr<IEntity> collision_entity) override;

 private:
  void Init();

};

#endif //LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITYPIPE_HPP_
