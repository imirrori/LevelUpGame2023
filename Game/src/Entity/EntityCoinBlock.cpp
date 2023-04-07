//
// Created by Dmitry Morozov on 7/4/23.
//

#include "Entity/EntityCoinBlock.hpp"

EntityCoinBlock::EntityCoinBlock(EventSystem &event_handler, b2World &world, glm::vec2 position, glm::vec2 scale) {

}
EntityCoinBlock::~EntityCoinBlock() {

}
void EntityCoinBlock::onUpdate(float delta) {
  Entity::onUpdate(delta);
}
void EntityCoinBlock::onRender() {
  Entity::onRender();
}
void EntityCoinBlock::onCollision(std::shared_ptr<IEntity> collision_entity) {
  Entity::onCollision(collision_entity);
}
