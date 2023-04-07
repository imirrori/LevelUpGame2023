//
// Created by Dmitry Morozov on 4/4/23.
//

#ifndef MARIO_GAME_INCLUDE_IEVENTHANDLER_HPP_
#define MARIO_GAME_INCLUDE_IEVENTHANDLER_HPP_

#include "Entity/IEntity.hpp"

#include <memory>

class IEventHandler {
 public:
  virtual ~IEventHandler() = default;

  virtual const std::vector<IEntity *> getEventsList() = 0;

  virtual void addEventHandler(IEntity & owner) = 0;
  virtual void removeEventHandler(IEntity & owner) = 0;

};

#endif //MARIO_GAME_INCLUDE_IEVENTHANDLER_HPP_
