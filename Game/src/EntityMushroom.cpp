//
// Created by Dmitry Morozov on 25/3/23.
//

#include "EntityMushroom.hpp"
void EntityMushroom::onUpdate(double delta) {
  Entity::onUpdate(delta);
}
void EntityMushroom::onRender() {
  Entity::onRender();
}
void EntityMushroom::onCollision(std::shared_ptr<IEntity> collision_entity) {
  Entity::onCollision(collision_entity);
}
void EntityMushroom::Init() {

}
