//
// Created by Dmitry Morozov on 25/3/23.
//

#include "Game.hpp"
#include "Entity/EntityBlock.hpp"

EntityBlock::EntityBlock(b2World &world, glm::vec2 position, glm::vec2 scale) {

  vPosition = position;
  vScale = scale;
  vRotation = 0;
  vTag = "brick";

  textures[0] = Texture::GetTexture("brick-2");
  textures[1] = Texture::GetTexture("brick-1");
  textures[2] = Texture::GetTexture("brick-0");

  current_texture = textures[2];

  b2BodyDef b_def;

  b_def.userData.pointer = reinterpret_cast<uintptr_t>(this);
  b_def.position.Set(vPosition.x/Game::PIXEL_TO_M, vPosition.y/Game::PIXEL_TO_M);
  b_def.type = b2_dynamicBody;
  b_def.fixedRotation = true;
  b_def.gravityScale = 0;

  mp_Body = world.CreateBody(&b_def);

  b2PolygonShape b_shape;
  b_shape.SetAsBox(vScale.x/2.f/Game::PIXEL_TO_M, vScale.y/2.f/Game::PIXEL_TO_M);
  mp_Body->CreateFixture(&b_shape, 0.0f);
}

void EntityBlock::onUpdate(float delta) {
  vPosition = {mp_Body->GetPosition().x*Game::PIXEL_TO_M, mp_Body->GetPosition().y*Game::PIXEL_TO_M};
  vRotation = mp_Body->GetAngle();
}

void EntityBlock::onRender() {
  Entity::onRender();
}

void EntityBlock::onCollision(std::shared_ptr<IEntity> collision_entity) {
  Entity::onCollision(collision_entity);
}



