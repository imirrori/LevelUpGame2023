//
// Created by Dmitry Morozov on 29/3/23.
//

#ifndef LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITYMARIO_HPP_
#define LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITYMARIO_HPP_

#include "Entity/Entity.hpp"
#include "Texture.hpp"

#include <array>
#include <Box2D/Box2D.h>

class EntityMario : public Entity {
 public:
  explicit EntityMario(b2World &world);
  ~EntityMario() override;
  void onUpdate(float delta) override;
  void onRender() override;

  // physics
  void onCollision(std::shared_ptr<IEntity> collider) override;

 private:
  void Movement(float delta);
  void Flip();
  void RunAnimation(float delta);
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

  Texture::TexturePtr currentTexture;
  Texture::TexturePtr idleTexture;
  Texture::TexturePtr jumpTexture;

  std::array<Texture::TexturePtr, 3> runTexture;

  b2Body *mp_Body; // Make shared
};

#endif //LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITYMARIO_HPP_
