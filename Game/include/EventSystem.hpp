//
// Created by Dmitry Morozov on 4/4/23.
//

#ifndef MARIO_GAME_SRC_EVENTSYSTEM_HPP_
#define MARIO_GAME_SRC_EVENTSYSTEM_HPP_

#include "Entity/Entity.hpp"
#include "interface/IEntity.hpp"
#include "interface/IEventHandler.hpp"

#include <memory>

class EventSystem : public IEventHandler {
 public:
	EventSystem();
	~EventSystem() override;

	std::vector<std::shared_ptr<IEntity>> getEventsList() override { return m_eventHandlers; }

	void addEventHandler(std::shared_ptr<Entity> owner) override;
	void removeEventHandler(std::shared_ptr<Entity> owner) override;

 private:
	std::vector<std::shared_ptr<IEntity>> m_eventHandlers; // Vector of event handlers

};

#endif //MARIO_GAME_SRC_EVENTSYSTEM_HPP_
