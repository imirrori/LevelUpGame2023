//
// Created by Dmitry Morozov on 24/3/23.
//

#ifndef LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_LEVEL_HPP_
#define LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_LEVEL_HPP_

#include "Entity/Entity.hpp"
#include "Map.hpp"

#include <box2d/box2d.h>
#include <string>
#include <vector>

class Level : public Entity {
 public:
  explicit Level(b2World &world);
  ~Level() override;

  void onUpdate(float delta) override;
  void onRender() override;
  void onCollision(std::shared_ptr<IEntity> collision_entity) override;

 private:
  std::vector<std::shared_ptr<Entity>> map_entities;
  Map map_;

  void buildMap(b2World &world);

};

#endif //LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_LEVEL_HPP_
