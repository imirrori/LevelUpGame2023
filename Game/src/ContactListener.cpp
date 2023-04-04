//
// Created by Dmitry Morozov on 31/3/23.
//

#include "ContactListener.hpp"

ContactListener::ContactListener(b2World &MarioWorld) {
  MarioWorld.SetContactListener(this);
}

ContactListener::~ContactListener() {

}

void ContactListener::BeginContact(b2Contact *contact) {
  b2Body *bodyA = contact->GetFixtureA()->GetBody();
  b2Body *bodyB = contact->GetFixtureB()->GetBody();

  auto objA = (Entity *)bodyA->GetUserData().pointer;
  auto objB = (Entity *)bodyB->GetUserData().pointer;

  if (objA && objB) {
	objA->onCollision(std::make_shared<Entity>(*objB));
	objB->onCollision(std::make_shared<Entity>(*objA));
  }
}