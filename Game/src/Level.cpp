//
// Created by Dmitry Morozov on 24/3/23.
//

#include "Entity.hpp"
#include "EntityBlock.hpp"
#include "EntityCoin.hpp"
#include "EntityMushroom.hpp"
#include "EntityPipe.hpp"
#include "EntityStar.hpp"
#include "Level.hpp"

#include <memory>

void Level::onUpdate() {

}
void Level::onRender() {

}
void Level::onCollision() {

}
void Level::Init() {

  for (std::size_t i = 0; i < map_.height(); ++i) {

	for (std::size_t j = 0; j < map_.width(); ++j) {

	  switch (map_.GetMap()[i*map_.width() + j]) {
		case 'b':
		  map_entities.emplace_back(std::make_shared<Entity>(EntityBlock({j*100, (map_.height() - i)*100 + 100},
																		 {100, 100})));
		  break;

		case 'c':
		  map_entities.emplace_back(std::make_shared<Entity>(EntityCoin({j*100, (map_.height() - i)*100 + 100},
																		{100, 100})));
		  break;

		case 'p':
		  map_entities.emplace_back(std::make_shared<Entity>(EntityPipe({j*100, (map_.height() - i)*100 +
			  50}, {200, 200})));
		  break;

		case 'm':
		  map_entities.emplace_back(std::make_shared<Entity>(EntityMushroom({j*100, (map_.height() - i)*100 +
			  100}, {100, 100})));
		  break;

		case 's':
		  map_entities.emplace_back(std::make_shared<Entity>(EntityStar({j*100, (map_.height() - i)*100 +
			  100}, {100, 100})));

		default: break;
	  }

	}
  }
}

