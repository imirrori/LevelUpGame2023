//
// Created by Dmitry Morozov on 27/4/23.
//

#ifndef MARIO_GAME_INCLUDE_MENU_GAMESTATE_HPP_
#define MARIO_GAME_INCLUDE_MENU_GAMESTATE_HPP_

#include "GameState.hpp"
#include "GAME_STATES.hpp"

#include <stack>

class GameState {
 public:
	GameState();
	~GameState() = default;

	static void pushState(State::GAME_STATES state);
	static void popState();
	static void changeState(State::GAME_STATES state);
	static State::GAME_STATES peekState();
	static void swapState(State::GAME_STATES state);

 private:
	static std::stack<State::GAME_STATES> states;
};

#endif //MARIO_GAME_INCLUDE_MENU_GAMESTATE_HPP_
