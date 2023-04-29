//
// Created by Dmitry Morozov on 7/4/23.
//

#ifndef MARIO_GAME_SRC_ENTITY_ENTITYCOINBLOCK_HPP_
#define MARIO_GAME_SRC_ENTITY_ENTITYCOINBLOCK_HPP_

#include "box2d/box2d.h"
#include "glm/vec2.hpp"

#include "Entity/Entity.hpp"
#include "Entity/EntityCoin.hpp"
#include "EventSystem.hpp"
#include "Texture.hpp"

class EntityCoinBlock : public Entity {
 public:
	EntityCoinBlock(EventSystem &event_handler, b2World &world, glm::vec2 position, glm::vec2 scale);
	~EntityCoinBlock() override;

	void onUpdate(float delta) override;
	void onRender() override;
	void onCollision(std::shared_ptr<IEntity> collision_entity) override;

 private:
	EntityCoin *coin_;

	std::shared_ptr<Graphics::Texture> current_texture;
	std::shared_ptr<Graphics::Texture> idle_texture;
	std::shared_ptr<Graphics::Texture> break_texture;

	b2Body *mp_Body;

};

#endif //MARIO_GAME_SRC_ENTITY_ENTITYCOINBLOCK_HPP_
