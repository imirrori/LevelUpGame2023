//
// Created by Dmitry Morozov on 25/3/23.
//

#ifndef LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITYGROUND_HPP_
#define LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITYGROUND_HPP_

#include "GL/glew.h"

#include "Entity.hpp"
#include "EventSystem.hpp"
#include "Texture.hpp"

#include "box2d/box2d.h"

class EntityGround : public Entity {

 public:
  EntityGround(EventSystem &event_handler, b2World &world);
  ~EntityGround() override;

  void onUpdate(float delta) override;
  void onRender() override;
  void onCollision(std::shared_ptr<IEntity> collision_entity) override;

 private:
  Texture::TexturePtr texture;
  b2Body *mp_Body;

  int width_count_ = 200;
  float tile_width_ = 100;

};

#endif //LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITYGROUND_HPP_
