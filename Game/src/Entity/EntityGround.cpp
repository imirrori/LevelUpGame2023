//
// Created by Dmitry Morozov on 25/3/23.
//

#include "Entity/EntityGround.hpp"
#include "Graphics/Render.hpp"

EntityGround::EntityGround(b2World &MarioWorld) {

  vTag = "ground";
  texture = Texture::GetTexture("ground");

  b2BodyDef bodyDef;
  bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
  bodyDef.position.Set(tile_width*static_cast<float>(width_count)/2/pixel_to_m(), 100/pixel_to_m());
  mp_Body = MarioWorld.CreateBody(&bodyDef);

  b2PolygonShape groundShape;
  groundShape.SetAsBox(tile_width*static_cast<float>(width_count)/2/pixel_to_m(), 50/pixel_to_m());
  mp_Body->CreateFixture(&groundShape, 0.0f);
}
void EntityGround::SetTag(std::string &tag) {
  vTag = tag;
}

EntityGround::~EntityGround() {
  texture.reset();
}

void EntityGround::onUpdate(float delta) {

}

void EntityGround::onRender() {
  for (int i = 0; i < width_count; i++) {
	Render::DrawTexture({static_cast<float>(i)*tile_width, 100}, 0, {tile_width + 14.5f, tile_width + 20.f}, texture);
  }
}

void EntityGround::onCollision(std::shared_ptr<IEntity> collision_entity) {

}
void EntityGround::onInit() {
  Entity::onInit();
}
