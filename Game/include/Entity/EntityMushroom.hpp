//
// Created by Dmitry Morozov on 25/3/23.
//

#ifndef LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITYMUSHROOM_HPP_
#define LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITYMUSHROOM_HPP_

#include "GL/glew.h"

#include "Entity.hpp"
#include "EventSystem.hpp"
#include "Texture.hpp"

class EntityMushroom : public Entity {
 public:
  EntityMushroom(EventSystem &event_handler, b2World &world, glm::vec2 position, glm::vec2 scale);
  ~EntityMushroom() override;

  void onUpdate(float delta) override;
  void onRender() override;
  void onCollision(IEntity *collision_entity) override;

 private:
  void RunAnimation(float delta);
  void CountToDie(float delta);

  bool isAlive = true;
  bool isDie = false;

  float time_to_disappear_ = 1.f;
  float speed_ = 2.f;
  bool faceRight_ = false;

  Texture *current_texture;
  Texture *run_texture[2];
  Texture *dead_texture;

  // Animations

  int texture_index = 0;
  float animation_speed = 0.1f;
  float animation_time_btw = animation_speed;

  b2Body *mp_Body;

};

#endif //LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITYMUSHROOM_HPP_
