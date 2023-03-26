//
// Created by Dmitry Morozov on 25/3/23.
//

#include "EntityBlock.hpp"
void EntityBlock::onUpdate(double delta) {
  Entity::onUpdate(delta);
}
void EntityBlock::onRender() {
  Entity::onRender();
}
void EntityBlock::onCollision(std::shared_ptr<IEntity> collision_entity) {
  Entity::onCollision(collision_entity);
}
void EntityBlock::Init() {

}
void EntityBlock::onInit() {
  Entity::onInit();
}
