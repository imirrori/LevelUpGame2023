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

  IEntity *objA = (IEntity *)bodyA->GetUserData().pointer;
  IEntity *objB = (IEntity *)bodyB->GetUserData().pointer;

  if (objA && objB) {

	objA->onCollision(objB);
	objB->onCollision(objA);

  }
}