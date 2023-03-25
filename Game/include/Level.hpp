//
// Created by Dmitry Morozov on 24/3/23.
//

#ifndef LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_LEVEL_HPP_
#define LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_LEVEL_HPP_

#include "Entity.hpp"
#include "Map.hpp"

#include <string>
#include <vector>

class Level : public IEntity {
 public:
  Level() = default;
  ~Level() override;

  void onUpdate(double delta) override;
  void onRender() override;
  void onCollision(std::shared_ptr<IEntity> collision_entity) override;

 private:
  void Init();
  std::vector<std::shared_ptr<Entity>> map_entities;
  Map map_;



};

#endif //LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_LEVEL_HPP_
