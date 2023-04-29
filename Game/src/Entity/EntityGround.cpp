//
// Created by Dmitry Morozov on 25/3/23.
//

#include "Entity/EntityGround.hpp"
#include "EventSystem.hpp"
#include "Graphics/Render.hpp"

EntityGround::EntityGround(EventSystem &event_handler, b2World &world, int width_count) : width_count_(width_count) {

	event_handler.addEventHandler(std::shared_ptr<Entity>(this));

	vTag = "ground";

	texture = std::make_shared<Graphics::Texture>(Graphics::Texture::GetTexture("ground"));

	b2BodyDef bodyDef;

	bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
	bodyDef.position.Set(tile_width_ * width_count_ / 2 / pixelToM_, 100 / pixelToM_);

	mp_Body = world.CreateBody(&bodyDef);

	b2PolygonShape groundShape;

	groundShape.SetAsBox(tile_width_ * width_count_ / 2 / pixelToM_, 50 / pixelToM_);
	mp_Body->CreateFixture(&groundShape, 0.0f);
}

EntityGround::~EntityGround() {

}

void EntityGround::onUpdate(float delta) {

}

void EntityGround::onRender() {

	for (int i = 0; i < width_count_; i++) {
		Graphics::Render::DrawTexture({static_cast<float>(i) * tile_width_, 100},
									  0,
									  {tile_width_ + 14.5f, tile_width_ + 20.f},
									  *texture);
	}

}

void EntityGround::onCollision(std::shared_ptr<IEntity> collision_entity) {

}
