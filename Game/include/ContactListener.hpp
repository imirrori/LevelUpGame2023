//
// Created by Dmitry Morozov on 31/3/23.
//

#ifndef LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_CONTACTLISTENER_HPP_
#define LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_CONTACTLISTENER_HPP_

#include "GL/glew.h"

#include "box2d/box2d.h"
#include "Entity/Entity.hpp"

class ContactListener : public b2ContactListener {
 public:
 public:
  ContactListener(b2World& physicsWorld);
  ~ContactListener();

  void BeginContact(b2Contact* contact) override;
};



#endif //LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_CONTACTLISTENER_HPP_
