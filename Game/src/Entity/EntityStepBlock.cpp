//
// Created by Dmitry Morozov on 7/4/23.
//

#include "Entity/Entity.hpp"
#include "Entity/EntityStepBlock.hpp"
#include "Graphics/Render.hpp"

EntityStepBlock::EntityStepBlock(EventSystem &event_handler_, b2World &world, glm::vec2 position, glm::vec2 scale) {
  event_handler_.addEventHandler(*this);

  vPosition = position;
  vRotation = 0;
  vScale = scale;

  texture = &Texture::GetTexture("stair_brick");

  b2BodyDef b_def;

  b_def.userData.pointer = reinterpret_cast<uintptr_t>(this);
  b_def.position.Set(vPosition.x/pixelToM_, vPosition.y/pixelToM_);
  b_def.fixedRotation = true;

  mp_Body = world.CreateBody(&b_def);

  b2PolygonShape b_shape;

  b_shape.SetAsBox(vScale.x/2.f/pixelToM_, vScale.y/2.f/pixelToM_);

  mp_Body->CreateFixture(&b_shape, 0.0f);

}

EntityStepBlock::~EntityStepBlock() {

  mp_Body->GetWorld()->DestroyBody(mp_Body);

}

void EntityStepBlock::onUpdate(float dt) {

}

void EntityStepBlock::onRender() {

  Render::DrawTexture(vPosition, vRotation, vScale, *texture);

}

void EntityStepBlock::onCollision(IEntity *collision_entity) {

}

