//
// Created by Dmitry Morozov on 25/3/23.
//

#include "Game.hpp"
#include "Graphics/Render.hpp"
#include "Entity/EntityBlock.hpp"

EntityBlock::EntityBlock(EventSystem &event_handler_, b2World &world, glm::vec2 position, glm::vec2 scale) {

  vPosition = position;
  vScale = scale;
  vRotation = 0;
  vTag = "brick";

  event_handler_.addEventHandler(*this);

  textures[0] = Texture::GetTexture("brick-2");
  textures[1] = Texture::GetTexture("brick-1");
  textures[2] = Texture::GetTexture("brick-0");

  current_texture = textures[2];

  b2BodyDef b_def;

  b_def.userData.pointer = reinterpret_cast<uintptr_t>(this);

  b_def.position.Set(vPosition.x/pixelToM_, vPosition.y/pixelToM_);
  b_def.type = b2_dynamicBody;
  b_def.fixedRotation = true;
  b_def.gravityScale = 0;

  mp_Body = world.CreateBody(&b_def);

  b2PolygonShape b_shape;

  b_shape.SetAsBox(vScale.x/2.f/pixelToM_, vScale.y/2.f/pixelToM_);
  mp_Body->CreateFixture(&b_shape, 0.0f);

}

void EntityBlock::onUpdate(float delta) {

  vPosition = {mp_Body->GetPosition().x*pixelToM_, mp_Body->GetPosition().y*pixelToM_};
  vRotation = mp_Body->GetAngle();

}

void EntityBlock::onRender() {

  if (hp_ > 0) {
	Render::DrawTexture(vPosition, vRotation, vScale, current_texture);
  }
}

void EntityBlock::onCollision(std::shared_ptr<IEntity> collision_entity) {

  if (collision_entity->GetTag()=="mario") {

	if (collision_entity->GetPosition().y < vPosition.y) {
	  hp_--;

	  if (hp_ <= 0) {
		mp_Body->GetFixtureList()->SetSensor(true);
	  }

	  current_texture = textures[hp_ - 1];
	}
  }
}



