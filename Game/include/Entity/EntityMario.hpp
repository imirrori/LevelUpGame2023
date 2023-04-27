//
// Created by Dmitry Morozov on 29/3/23.
//

#ifndef LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITYMARIO_HPP_
#define LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITYMARIO_HPP_

#include "box2d/box2d.h"
#include "GL/glew.h"

#include "Entity/Entity.hpp"
#include "EventSystem.hpp"
#include "GAME_STATES.hpp"
#include "GameState.hpp"
#include "Texture.hpp"

#include <array>

class EntityMario : public Entity {

 public:
	EntityMario(EventSystem &event_handler, b2World &world);
	~EntityMario() override;

	void onUpdate(float delta) override;
	void onRender() override;
	void onCollision(IEntity *collider) override;

 private:
	void Movement(float delta);


	void Flip();
	void RunAnimation(float delta);
	void Jump(b2Vec2 &vel);
	void LittleJump();

	float speed = 5.f;
	bool jumping = false;
	float jumpForce = 17;
	bool faceRight = true;

	int texture_index = 0;
	float animation_speed = 0.1f;
	float animation_time_btw = animation_speed;

	GameState &game_state_ = GameState::getInstance();

	Graphics::Texture *currentTexture;
	Graphics::Texture *idleTexture;
	Graphics::Texture *jumpTexture;

	Graphics::Texture *runTexture[3];

	b2Body *mp_Body; // Make shared
};

#endif //LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITYMARIO_HPP_
