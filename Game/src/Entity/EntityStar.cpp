//
// Created by Dmitry Morozov on 25/3/23.
//

#include "Entity/EntityStar.hpp"
void EntityStar::onUpdate(float delta) {
  Entity::onUpdate(delta);
}
void EntityStar::onRender() {
  Entity::onRender();
}
void EntityStar::onCollision(std::shared_ptr<IEntity> collision_entity) {
  Entity::onCollision(collision_entity);
}
void EntityStar::Init() {

}
