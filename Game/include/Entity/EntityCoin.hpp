//
// Created by Dmitry Morozov on 25/3/23.
//

#ifndef LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITYCOIN_HPP_
#define LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITYCOIN_HPP_

#include "GL/glew.h"

#include "Entity.hpp"
#include "EventSystem.hpp"
#include "Texture.hpp"

class EntityCoin : public Entity {

 public:

  EntityCoin(EventSystem &event_handler_, b2World &world, glm::vec2 position, glm::vec2 scale);

  ~EntityCoin() override;

  void onUpdate(float delta) override;
  void onRender() override;
  void onCollision(IEntity *collision_entity) override;

  void EngageCoin();

 private:

  void Animation(float dt);

  bool isAlive = false;
  glm::vec2 engage_pos_;
  bool startCount = false;
  float show_time = 1.5f;
  float show_time_btw = show_time;

  int texture_index_ = 0;

  float animation_speed = 0.05f;
  float animation_time_btw = animation_speed;

  Graphics::Texture *current_texture;
  Graphics::Texture *textures[6];

  b2Body *mp_Body;

};

#endif //LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITYCOIN_HPP_
