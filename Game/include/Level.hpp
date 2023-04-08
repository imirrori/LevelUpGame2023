//
// Created by Dmitry Morozov on 24/3/23.
//

#ifndef LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_LEVEL_HPP_
#define LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_LEVEL_HPP_

#include "box2d/box2d.h"
#include "GL/glew.h"

#include "Entity/Entity.hpp"
#include "EventSystem.hpp"
#include "interface/ILevel.hpp"
#include "Map.hpp"

#include <string>
#include <vector>

class Level : public Entity { //TODO: Refactor to ILevel
 public:
  Level(EventSystem &event_handler, b2World &world);
  ~Level() override;

  void onUpdate(float delta) override;
  void onRender() override;
  void onCollision(IEntity *collision_entity) override;

 private:
  std::vector<IEntity *> map_entities;
  Map map_;

  EventSystem event_handler_;

  void buildMap(b2World &world);

};

#endif //LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_LEVEL_HPP_
