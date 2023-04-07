//
// Created by Dmitry Morozov on 25/3/23.
//

#ifndef LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITYPIPE_HPP_
#define LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITYPIPE_HPP_

#include "GL/glew.h"

#include "Entity.hpp"
#include "EventSystem.hpp"
#include "Texture.hpp"

class EntityPipe : public Entity {
 public:
  EntityPipe(EventSystem &event_holder, b2World &world, glm::vec2 position, glm::vec2 scale);
  ~EntityPipe() override;

  void onUpdate(float delta) override;
  void onRender() override;
  void onCollision(std::shared_ptr<IEntity> collision_entity) override;

 private:
  Texture::TexturePtr texture;
  b2Body *mp_Body;

};

#endif //LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITYPIPE_HPP_
