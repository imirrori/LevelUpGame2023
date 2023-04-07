//
// Created by Dmitry Morozov on 25/3/23.
//

#include "glm/glm.hpp"

#include "Entity/EntityMushroom.hpp"
#include "Graphics/Render.hpp"

EntityMushroom::EntityMushroom(EventSystem &event_handler, b2World &world, glm::vec2 position, glm::vec2 scale) {

  vPosition = position;
  vRotation = 0;
  vScale = scale;

  event_handler.addEventHandler(*this);

  run_texture[0] = Texture::GetTexture("mushroom-run-0");
  run_texture[1] = Texture::GetTexture("mushroom-run-1");
  dead_texture = Texture::GetTexture("mushroom-dead");

  current_texture = run_texture[0];

  vTag = "mushroom";

  b2BodyDef b_def;

  b_def.userData.pointer = reinterpret_cast<uintptr_t>(this);
  b_def.type = b2_dynamicBody;
  b_def.fixedRotation = true;

  b_def.position.Set(vPosition.x/pixelToM_, vPosition.y/pixelToM_);

  b_def.angle = glm::radians(vRotation);

  this->mp_Body = world.CreateBody(&b_def);

  b2PolygonShape box_shape;

  box_shape.SetAsBox(vScale.x/2.f/pixelToM_, vScale.y/2.f/pixelToM_);

  b2FixtureDef fixDef;

  fixDef.shape = &box_shape;
  fixDef.density = 1;
  fixDef.friction = 0.3f;

  this->mp_Body->CreateFixture(&fixDef);

}

void EntityMushroom::onUpdate(float delta) {

  if (!isAlive) {
	return;
  }

  vPosition = {mp_Body->GetPosition().x*150, mp_Body->GetPosition().y*150};
  vRotation = glm::degrees(mp_Body->GetAngle());

  b2Vec2 vel = mp_Body->GetLinearVelocity();

  if (faceRight_) {

	vel.x = speed_;

  } else {

	vel.x = -speed_;

  }

  mp_Body->SetLinearVelocity(vel);

  if (isDie) {

	CountToDie(delta);

  }

  if (current_texture!=dead_texture) {

	RunAnimation(delta);

  }
}

void EntityMushroom::onRender() {

  if (!isAlive) {

	return;
  }

  Render::DrawTexture(vPosition, vRotation, vScale, current_texture);

}

void EntityMushroom::onCollision(std::shared_ptr<IEntity> collision_entity) {
  Entity::onCollision(collision_entity);
}

EntityMushroom::~EntityMushroom() {

  run_texture[0].reset();
  run_texture[1].reset();
  current_texture.reset();
  dead_texture.reset();

}


