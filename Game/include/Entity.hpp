//
// Created by Dmitry Morozov on 24/3/23.
//

#ifndef LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITY_HPP_
#define LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITY_HPP_

#include "IEntity.hpp"

class Entity : public IEntity{
 public:
  Entity() = default;
  ~Entity() override = default;

  void onUpdate() override;
  void onRender() override;
  void onCollision() override;

};

#endif //LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITY_HPP_
