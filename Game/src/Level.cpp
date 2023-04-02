//
// Created by Dmitry Morozov on 24/3/23.
//

#include "Game/include/Entity/Entity.hpp"
#include "Game/include/Entity/EntityBlock.hpp"
#include "Game/include/Entity/EntityCoin.hpp"
#include "Game/include/Entity/EntityMushroom.hpp"
#include "Game/include/Entity/EntityPipe.hpp"
#include "Game/include/Entity/EntityStar.hpp"
#include "Level.hpp"

#include <memory>

void Level::onUpdate(float delta) {

}
void Level::onRender() {

}
void Level::onCollision(std::shared_ptr<IEntity> collision_entity) {

}
void Level::buildMap(b2World &world) {

  for (std::size_t i = 0; i < map_.height(); ++i) {

	for (std::size_t j = 0; j < map_.width(); ++j) {

	  switch (map_.GetMap()[i*map_.width() + j]) {
		case 'b':
		  map_entities.emplace_back(std::make_shared<Entity>(EntityBlock(world, {j*100, (map_.height() - i)*100 + 100},
																		 {100, 100})));
		  break;

		case 'c':
		  map_entities.emplace_back(std::make_shared<Entity>(EntityCoin(world, {j*100, (map_.height() - i)*100 + 100},
																		{100, 100})));
		  break;

		case 'p':
		  map_entities.emplace_back(std::make_shared<Entity>(EntityPipe(world, {j*100, (map_.height() - i)*100 +
			  50}, {200, 200})));
		  break;

		case 'm':
		  map_entities.emplace_back(std::make_shared<Entity>(EntityMushroom(world, {j*100, (map_.height() - i)*100 +
			  100}, {100, 100})));
		  break;

		case 's':
		  map_entities.emplace_back(std::make_shared<Entity>(world, EntityStar({j*100, (map_.height() - i)*100 +
			  100}, {100, 100})));

		default: break;
	  }

	}
  }
}
Level::~Level() {

  for (auto &entity : map_entities) {
	entity.reset();
  }

}

Level::Level(b2World &world) {

  buildMap(world);

}



