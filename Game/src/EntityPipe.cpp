//
// Created by Dmitry Morozov on 25/3/23.
//

#include "EntityPipe.hpp"
void EntityPipe::onUpdate(double delta) {
  Entity::onUpdate(delta);
}
void EntityPipe::onRender() {
  Entity::onRender();
}
void EntityPipe::onCollision(std::shared_ptr<IEntity> collision_entity) {
  Entity::onCollision(collision_entity);
}
void EntityPipe::Init() {

}
