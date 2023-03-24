//
// Created by Dmitry Morozov on 24/3/23.
//

#ifndef LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_LEVEL_HPP_
#define LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_LEVEL_HPP_

#include "Entity.hpp"

#include <string>
#include <vector>

class Level : public Entity {
 public:
  Level() = default;
  ~Level() override = default;

  void onUpdate() override;
  void onRender() override;
  void onCollision() override;

 private:
  std::vector<Entity> map_entities;
  const std::string map_;



};

#endif //LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_LEVEL_HPP_
