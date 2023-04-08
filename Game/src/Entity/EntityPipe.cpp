//
// Created by Dmitry Morozov on 25/3/23.
//

#include "Entity/EntityPipe.hpp"
#include "Graphics/Render.hpp"

void EntityPipe::onUpdate(float delta) {

}

void EntityPipe::onRender() {

  Render::DrawTexture(vPosition, vRotation, vScale, *texture);

}

void EntityPipe::onCollision(IEntity *collision_entity) {

}

EntityPipe::EntityPipe(EventSystem &event_holder, b2World &world, glm::vec2 position, glm::vec2 scale) {

  event_holder.addEventHandler(*this);

  vPosition = position;
  vScale = scale;
  vRotation = 0;
  vTag = "pipe";

  texture = &Texture::GetTexture("pipe");

  b2BodyDef b_def;

  b_def.userData.pointer = reinterpret_cast<uintptr_t>(this);
  b_def.type = b2_staticBody;

  b_def.position.Set(vPosition.x/pixelToM_, vPosition.y/pixelToM_);
  mp_Body = world.CreateBody(&b_def);

  b2PolygonShape b_shape;

  b_shape.SetAsBox(scale.x/2/pixelToM_, scale.y/2/pixelToM_);
  mp_Body->CreateFixture(&b_shape, 0.0);

}
EntityPipe::~EntityPipe() {

  mp_Body->GetWorld()->DestroyBody(mp_Body);

}
