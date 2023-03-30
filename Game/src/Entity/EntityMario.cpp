//
// Created by Dmitry Morozov on 29/3/23.
//

#include "Entity/EntityMario.hpp"
#include "Input.hpp"
#include "Graphics/Render.hpp"

#include <memory>

EntityMario::EntityMario(b2World &MarioWorld) : Entity() {

  vPosition = glm::vec2(800, 2000);
  vRotation = 0;
  vScale = glm::vec2(100, 100);
  vTag = "mario";

  idleTexture = Texture::GetTexture("mario-idle");
  jumpTexture = Texture::GetTexture("mario-jump");
  runTexture[0] = Texture::GetTexture("mario-run-0");
  runTexture[1] = Texture::GetTexture("mario-run-1");
  runTexture[2] = Texture::GetTexture("mario-run-2");

  currentTexture = idleTexture;

  // physics init
  b2BodyDef b_def;
  b_def.userData.pointer = reinterpret_cast<uintptr_t>(this);
  b_def.type = b2_dynamicBody;
  b_def.fixedRotation = true;
  b_def.gravityScale = 2.f;
  b_def.position.Set(vPosition.x/pixel_to_m(), vPosition.y/pixel_to_m());
  b_def.angle = glm::radians(vRotation);

  this->mp_Body = MarioWorld.CreateBody(&b_def);
  b2PolygonShape box_shape;
  box_shape.SetAsBox(vScale.x/2.f/pixel_to_m(), vScale.y/2.f/pixel_to_m());

  b2FixtureDef fixDef;
  fixDef.shape = &box_shape;
  fixDef.density = 1;
  fixDef.friction = 1.f;
  this->mp_Body->CreateFixture(&fixDef);
}

EntityMario::~EntityMario() {
  mp_Body->GetWorld()->DestroyBody(mp_Body);

  // Delete textures
  idleTexture.reset();
  jumpTexture.reset();
  runTexture[0].reset();
  runTexture[1].reset();
  runTexture[2].reset();
  currentTexture.reset();

}

void EntityMario::onUpdate(float delta) {

  vPosition = {mp_Body->GetPosition().x*150, mp_Body->GetPosition().y*150};
  vRotation = glm::degrees(mp_Body->GetAngle());

  Movement(delta);

  // Animation
  if ((Input::GetKey(GLFW_KEY_LEFT) || Input::GetKey(GLFW_KEY_RIGHT))!=0 && !jumping) {
	RunAnimation(delta);
  } else if (jumping) {
	currentTexture = jumpTexture;
  } else if (currentTexture!=idleTexture && !jumping) {
	currentTexture = idleTexture;
  }

  // Flipping
  if ((Input::GetKey(GLFW_KEY_LEFT) && faceRight) || (Input::GetKey(GLFW_KEY_RIGHT) && !faceRight)) {
	Flip();
  }

}

void EntityMario::onRender() {
  Render::DrawTexture(vPosition, vRotation, vScale, currentTexture);
}

void EntityMario::Movement(float delta) {
  b2Vec2 vel = mp_Body->GetLinearVelocity();
  if (Input::GetKey(GLFW_KEY_LEFT))
	vel.x = -speed;
  else if (Input::GetKey(GLFW_KEY_RIGHT))
	vel.x = speed;

  // Jump
  if (Input::GetKeyDown(GLFW_KEY_SPACE))
	Jump(vel);

  mp_Body->SetLinearVelocity(vel);
}

void EntityMario::Jump(b2Vec2 &vel) {
  if (!jumping) {
	jumping = true;
	vel.y = jumpForce;
	currentTexture = jumpTexture;
  }
}

void EntityMario::LittleJump() {
  b2Vec2 vel = mp_Body->GetLinearVelocity();
  vel.y = 10;
  currentTexture = jumpTexture;
  mp_Body->SetLinearVelocity(vel);
}

void EntityMario::onCollision(std::shared_ptr<IEntity> collider) {
  jumping = false;
  if (collider->GetTag()=="mushroom")
	LittleJump();
}

void EntityMario::Flip() {
  faceRight = !faceRight;
  vScale.x *= -1;
}

void EntityMario::RunAnimation(float delta) {
  currentTexture = runTexture[texture_index];

  if (animation_time_btw > 0) {
	animation_time_btw -= delta;
  } else {
	animation_time_btw = animation_speed;
	texture_index++;
	if (texture_index >= 3)
	  texture_index = 0;
  }
}