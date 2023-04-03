//
// Created by Dmitry Morozov on 25/3/23.
//

#ifndef LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITYGROUND_HPP_
#define LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITYGROUND_HPP_

#include "GL/glew.h"

#include "Entity.hpp"
#include "Texture.hpp"

#include "box2d/box2d.h"


class EntityGround : public Entity {
 public:
  explicit EntityGround(b2World &world);
  ~EntityGround() override;

  void onInit() override;
  void onUpdate(float delta) override;
  void onRender() override;
  void onCollision(std::shared_ptr<IEntity> collision_entity) override;
  void SetTag(std::string &tag) override;

 private:
  std::string vTag;
  Texture::TexturePtr texture;
  b2Body *mp_Body;

  int width_count = 200;
  float tile_width = 100;
};

#endif //LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITYGROUND_HPP_
