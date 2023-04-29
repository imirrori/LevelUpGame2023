//
// Created by Dmitry Morozov on 4/4/23.
//

#ifndef MARIO_GAME_INCLUDE_IEVENTHANDLER_HPP_
#define MARIO_GAME_INCLUDE_IEVENTHANDLER_HPP_

#include "Entity/Entity.hpp"
#include "interface/IEntity.hpp"

#include <memory>

class IEventHandler {
 public:
	virtual ~IEventHandler() = default;

	virtual std::vector<std::shared_ptr<IEntity>> getEventsList() = 0;

	virtual void addEventHandler(std::shared_ptr<Entity> owner) = 0;
	virtual void removeEventHandler(std::shared_ptr<Entity> owner) = 0;

};

#endif //MARIO_GAME_INCLUDE_IEVENTHANDLER_HPP_
