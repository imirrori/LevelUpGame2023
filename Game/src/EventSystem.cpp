//
// Created by Dmitry Morozov on 4/4/23.
//

#include "EventSystem.hpp"

EventSystem::EventSystem() {

}

void EventSystem::addEventHandler(IEntity &owner) {
  m_eventHandlers.push_back(&owner);
}

void EventSystem::removeEventHandler(IEntity &owner) {

  for (int i = 0; i < m_eventHandlers.size(); i++) {

	if (m_eventHandlers[i]==&owner) {
	  m_eventHandlers.erase(m_eventHandlers.begin() + i);
	}

  }
}

EventSystem::~EventSystem() {

}
