//
// Created by Dmitry Morozov on 25/3/23.
//

#ifndef LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITYBLOCK_HPP_
#define LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITYBLOCK_HPP_

#include "box2d/box2d.h"
#include "GL/glew.h"
#include "glm/vec2.hpp"

#include "Entity.hpp"
#include "EventSystem.hpp"
#include "Texture.hpp"

class EntityBlock : public Entity {
 public:

	EntityBlock(EventSystem &event_handler_, b2World &world, glm::vec2 position, glm::vec2 scale);

	~EntityBlock() override;

	void onUpdate(float delta) override;
	void onRender() override;
	void onCollision(std::shared_ptr<IEntity> collision_entity) override;

 private:
//  const void Shake_(float delta);

	int hp_ = 3;

	std::shared_ptr<Graphics::Texture> current_texture;
	std::shared_ptr<Graphics::Texture> textures[3];

	b2Body *mp_Body;

};

#endif //LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_ENTITYBLOCK_HPP_
