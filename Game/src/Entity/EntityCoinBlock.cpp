//
// Created by Dmitry Morozov on 7/4/23.
//

#include "Entity/EntityCoinBlock.hpp"
#include "Graphics/Render.hpp"

EntityCoinBlock::EntityCoinBlock(EventSystem &event_handler, b2World &world, glm::vec2 position, glm::vec2 scale) {

  event_handler.addEventHandler(*this);

  vPosition = position;
  vRotation = 0;
  vScale = scale;
  vTag = "coin-brick";

  idle_texture = Texture::GetTexture("coin-brick-idle");
  break_texture = Texture::GetTexture("coin-brick-break");
  current_texture = idle_texture;

  b2BodyDef b_def;

  b_def.userData.pointer = reinterpret_cast<uintptr_t>(this);
  b_def.position.Set(vPosition.x/pixelToM_, vPosition.y/pixelToM_);
  b_def.fixedRotation = true;

  mp_Body = world.CreateBody(&b_def);

  b2PolygonShape b_shape;

  b_shape.SetAsBox(vScale.x/2/pixelToM_, vScale.y/2/pixelToM_);

  mp_Body->CreateFixture(&b_shape, 0.0f);

  coin_ = std::make_shared<EntityCoin>(event_handler, world, vPosition, vScale);
}

EntityCoinBlock::~EntityCoinBlock() {

  mp_Body->GetWorld()->DestroyBody(mp_Body);
  coin_.reset();

}

void EntityCoinBlock::onUpdate(float delta) {

}

void EntityCoinBlock::onRender() {

  Render::DrawTexture(vPosition, vRotation, vScale, current_texture);

}

void EntityCoinBlock::onCollision(std::shared_ptr<IEntity> collision_entity) {

  if (collision_entity->GetTag()=="mario" && collision_entity->GetPosition().y < vPosition.y) {

	if (current_texture==idle_texture) {

	  coin_->EngageCoin();
	  current_texture = break_texture;

	} else if (current_texture==break_texture) {
	  return;
	}
  }
}
