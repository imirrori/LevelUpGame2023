//
// Created by Dmitry Morozov on 25/3/23.
//

#include "Entity/EntityCoin.hpp"
#include "Graphics/Render.hpp"

void EntityCoin::onUpdate(float delta) {

  if (isAlive) {
	vPosition = {mp_Body->GetPosition().x*pixelToM_, mp_Body->GetPosition().y*pixelToM_};

	Animation(delta);
  }

  if (startCount) {

	if (show_time_btw <= 0) {

	  startCount = false;
	  isAlive = false;
	  show_time_btw = show_time;
	  mp_Body->SetGravityScale(0);

	} else {
	  show_time_btw -= delta;
	}
  }
}

void EntityCoin::onRender() {

  if (isAlive) {
	Render::DrawTexture(vPosition, vRotation, vScale, current_texture);
  }

}

EntityCoin::EntityCoin(EventSystem &event_handler_, b2World &world, glm::vec2 position, glm::vec2 scale) {

  event_handler_.addEventHandler(*this);

  vPosition = position;
  vRotation = 0;
  vScale = scale;

  engage_pos_ = position;

  textures[0] = Texture::GetTexture("coin-0");
  textures[1] = Texture::GetTexture("coin-1");
  textures[2] = Texture::GetTexture("coin-2");
  textures[3] = Texture::GetTexture("coin-3");
  textures[4] = Texture::GetTexture("coin-4");
  textures[5] = Texture::GetTexture("coin-5");

  current_texture = textures[0];

  b2BodyDef b_def;

  b_def.type = b2_dynamicBody;
  b_def.gravityScale = 0;
  b_def.fixedRotation = true;
  b_def.position.Set(vPosition.x/pixelToM_, vPosition.y/pixelToM_);

  mp_Body = world.CreateBody(&b_def);

  b2PolygonShape box_shape;
  box_shape.SetAsBox(vScale.x/2.f/pixelToM_, vScale.y/2.f/pixelToM_);

  b2FixtureDef fixDef;

  fixDef.shape = &box_shape;
  fixDef.density = 1;
  fixDef.friction = 1.f;

  this->mp_Body->CreateFixture(&fixDef);

  mp_Body->GetFixtureList()->SetSensor(true);

}

void EntityCoin::EngageCoin() {

  isAlive = true;
  startCount = true;

  mp_Body->SetGravityScale(3);
  b2Vec2 vel = mp_Body->GetLinearVelocity();

  vel.y = 15;

  mp_Body->SetLinearVelocity(vel);

}

void EntityCoin::onCollision(std::shared_ptr<IEntity> collision_entity) {

  // Not necessary
}
void EntityCoin::Animation(float dt) {

  if (animation_time_btw <= 0) {
	texture_index_++;

	if (texture_index_ >= 6) {
	  texture_index_ = 0;
	}

	current_texture = textures[texture_index_];
	animation_time_btw = animation_speed;

  } else {

	animation_time_btw -= dt;

  }

}

EntityCoin::~EntityCoin() {

  mp_Body->GetWorld()->DestroyBody(mp_Body);

}
