//
// Created by Dmitry Morozov on 29/3/23.
//

#include "Entity/EntityMario.hpp"
#include "EventSystem.hpp"
#include "Graphics/Render.hpp"
#include "Input.hpp"

#include <memory>

using STATE = State::GAME_STATES;

EntityMario::EntityMario(EventSystem &event_handler, b2World &world) {

	vPosition = glm::vec2(800, 2000);
	vRotation = 0;
	vScale = glm::vec2(100, 100);
	vTag = "mario";

	event_handler.addEventHandler(std::make_shared<Entity>(*this));

	idleTexture = std::make_shared<Graphics::Texture>(Graphics::Texture::GetTexture("mario-idle"));
	jumpTexture = std::make_shared<Graphics::Texture>(Graphics::Texture::GetTexture("mario-jump"));

	runTexture[0] = std::make_shared<Graphics::Texture>(Graphics::Texture::GetTexture("mario-run-0"));
	runTexture[1] = std::make_shared<Graphics::Texture>(Graphics::Texture::GetTexture("mario-run-1"));
	runTexture[2] = std::make_shared<Graphics::Texture>(Graphics::Texture::GetTexture("mario-run-2"));

	currentTexture = idleTexture;

	b2BodyDef b_def;

	b_def.userData.pointer = reinterpret_cast<uintptr_t>(this);

	b_def.type = b2_dynamicBody;
	b_def.fixedRotation = true;
	b_def.gravityScale = 2.f;

	b_def.position.Set(vPosition.x / pixelToM_, vPosition.y / pixelToM_);
	b_def.angle = glm::radians(vRotation);

	this->mp_Body = world.CreateBody(&b_def);
	b2PolygonShape box_shape;

	box_shape.SetAsBox(vScale.x / 2.f / pixelToM_, vScale.y / 2.f / pixelToM_);

	b2FixtureDef fixDef;

	fixDef.shape = &box_shape;
	fixDef.density = 1;
	fixDef.friction = 1.f;

	this->mp_Body->CreateFixture(&fixDef);

}

EntityMario::~EntityMario() {
	mp_Body->GetWorld()->DestroyBody(mp_Body);

}

void EntityMario::onUpdate(float delta) {

	vPosition = {mp_Body->GetPosition().x * 150, mp_Body->GetPosition().y * 150};
	vRotation = glm::degrees(mp_Body->GetAngle());

	Movement(delta);

	// Animation

	auto cur_gs_ = game_state_.peekState();

	if ((cur_gs_ == STATE::GS_MovingLeft || cur_gs_ == STATE::GS_MovingRight) && !jumping) {

		RunAnimation(delta);

	} else if (jumping) {

		currentTexture = jumpTexture;

	} else if (currentTexture != idleTexture && !jumping) {

		currentTexture = idleTexture;

	}

	// Flipping

	if (game_state_.peekState() == STATE::GS_MovingLeft) {

		Flip();

	} else if (game_state_.peekState() == STATE::GS_MovingRight) {

		Flip();

	}
}
void EntityMario::onRender() {

	Graphics::Render::DrawTexture(vPosition, vRotation, vScale, *currentTexture);

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

	if (collider->GetTag() == "mushroom") {
		LittleJump();
	}

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
void EntityMario::Movement(float delta) {

	b2Vec2 vel = mp_Body->GetLinearVelocity();

	auto cur_gs_ = game_state_.peekState();

	if (cur_gs_ == STATE::GS_MovingLeft) {

		vel.x = -speed;
	} else if (cur_gs_ == STATE::GS_MovingRight) {

		vel.x = speed;
	}
	// Jump
	if (cur_gs_ == STATE::GS_Jumping) {
		Jump(vel);
	}
	mp_Body->SetLinearVelocity(vel);
}
