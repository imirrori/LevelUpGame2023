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

  for (std::size_t y = 0; y < map_.height(); ++y) {

	for (std::size_t x = 0; x < map_.width(); ++x) {

	  switch (map_.GetMap()[y*map_.width() + x]) {
		case 'b':
		  map_entities.emplace_back(std::make_shared<Entity>(EntityBlock(event_handler_, world, {x*100, (map_.height()
			  - y)*100 + 100}, {100, 100})));
		  break;

		case 'c':
		  map_entities.emplace_back(std::make_shared<Entity>(EntityCoin(world, {x*100, (map_.height() - y)*100 + 100},
																		{100, 100})));
		  break;

		case 'p':
		  map_entities.emplace_back(std::make_shared<Entity>(EntityPipe(world, {x*100, (map_.height() - y)*100 +
			  50}, {200, 200})));
		  break;

		case 'm':
		  map_entities.emplace_back(std::make_shared<Entity>(EntityMushroom(world, {x*100, (map_.height() - y)*100 +
			  100}, {100, 100})));
		  break;

		case 's':
		  map_entities.emplace_back(std::make_shared<Entity>(EntityStar(world, {x*100, (map_.height() - y)*100 +
			  100}, {100, 100})));
		  break;

		default: break;
	  }

	}
  }
}
Level::~Level() {

//  for (auto &entity : map_entities) {
//	entity.reset();
//  }

}

Level::Level(EventSystem &event_handler, b2World &world) {

  event_handler_ = event_handler;

  buildMap(world);

  std::cout << "Level created" << std::endl;

}



