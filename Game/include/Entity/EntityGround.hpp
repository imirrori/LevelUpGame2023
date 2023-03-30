//
// Created by Dmitry Morozov on 25/3/23.
//

#ifndef LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITYGROUND_HPP_
#define LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITYGROUND_HPP_

#include "IEntity.hpp"

class EntityGround : public IEntity {
 public:
  ~EntityGround() override = default;

  void onInit() override;
  void onUpdate(float delta) override;
  void onRender() override;
  void onCollision(std::shared_ptr<IEntity> collision_entity) override;

 private:

};

#endif //LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITYGROUND_HPP_
