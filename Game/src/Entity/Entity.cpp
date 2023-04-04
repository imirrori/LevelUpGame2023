//
// Created by Dmitry Morozov on 24/3/23.
//

#include "Entity/Entity.hpp"

#include <iostream>

void Entity::onUpdate(float delta) {
  std::cerr << "Entity::onUpdate running, delta = " << delta << std::endl;

}

void Entity::onRender() {

}

void Entity::onCollision(std::shared_ptr<IEntity> collision_entity) {

}

void Entity::onInit() {

}

Entity::Entity() {

  this->vPosition = glm::vec2(0.0f, 0.0f);
  this->vRotation = 0.f;
  this->vScale = glm::vec2(1.0f, 1.0f);

}

