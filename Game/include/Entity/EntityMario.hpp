//
// Created by Dmitry Morozov on 29/3/23.
//

#ifndef LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITYMARIO_HPP_
#define LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITYMARIO_HPP_

#include "IEntity.hpp"
#include "Texture.hpp"

#include <Box2D/Box2D.h>

class EntityMario : public IEntity {
 public:
  EntityMario(b2World &MarioWorld);
  ~EntityMario();
  void onUpdate(double delta) override;
  void onRender() override;

  // physics
  void onCollision(std::shared_ptr<IEntity> collider) override;

 private:
  void Movement(double delta);
  void Flip();
  void RunAnimation(double delta);
  void Jump(b2Vec2 &vel);
  void LittleJump();

 private:
  float speed = 5.f;
  bool jumping = false;
  float jumpForce = 17;
  bool faceRight = true;

  int texture_index = 0;
  float animation_speed = 0.1f;
  float animation_time_btw = animation_speed;

  Texture *current_texture;
  Texture *idle_texture;
  Texture *jump_texture;
  Texture *run_texture[3];

  // Physics
  b2Body *mp_Body;
};

#endif //LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITYMARIO_HPP_
