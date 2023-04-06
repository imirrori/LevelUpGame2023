//
// Created by Dmitry Morozov on 25/3/23.
//

#include "Entity/EntityMushroom.hpp"

void EntityMushroom::onUpdate(float delta) {
  Entity::onUpdate(delta);
}

void EntityMushroom::onRender() {
  Entity::onRender();
}

void EntityMushroom::onCollision(std::shared_ptr<IEntity> collision_entity) {
  Entity::onCollision(collision_entity);
}


