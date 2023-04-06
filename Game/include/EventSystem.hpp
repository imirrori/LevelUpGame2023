//
// Created by Dmitry Morozov on 4/4/23.
//

#ifndef MARIO_GAME_SRC_EVENTSYSTEM_HPP_
#define MARIO_GAME_SRC_EVENTSYSTEM_HPP_

#include "Entity/IEntity.hpp"
#include "IEventHandler.hpp"

#include <memory>

class EventSystem : public IEventHandler {
 public:
  EventSystem();
  ~EventSystem() override = default;

  const std::vector<IEntity *> getEventsList() override { return m_eventHandlers; }

  void addEventHandler(IEntity &owner) override;
  void removeEventHandler(IEntity &owner) override;

 private:
  std::vector<IEntity *> m_eventHandlers;

};

#endif //MARIO_GAME_SRC_EVENTSYSTEM_HPP_
