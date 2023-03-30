//
// Created by Dmitry Morozov on 25/3/23.
//

#include "Entity/EntityCoin.hpp"
void EntityCoin::onUpdate(float delta) {
  Entity::onUpdate(delta);
}
void EntityCoin::onRender() {
  Entity::onRender();
}
void EntityCoin::onCollision(std::shared_ptr<IEntity> collision_entity) {
  Entity::onCollision(collision_entity);
}
void EntityCoin::Init() {

}
void EntityCoin::onInit() {
  Entity::onInit();
}
