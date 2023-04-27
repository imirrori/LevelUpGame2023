//
// Created by Dmitry Morozov on 27/4/23.
//

#include "GameState.hpp"

GameState::GameState() {

	states.push(State::GAME_STATES::GS_Loading);

}

void GameState::pushState(State::GAME_STATES state) {

	states.push(state);

}

void GameState::popState() {

	states.pop();

}

void GameState::changeState(State::GAME_STATES state) {

	if (not states.empty()) {
		states.pop();
	}

	states.push(state);

}

State::GAME_STATES GameState::peekState() {

	if (not states.empty()) {
		return states.top();
	}

	return State::GAME_STATES::GS_None;

}
void GameState::swapState(State::GAME_STATES state) {

	if (not states.empty()) {
		states.pop();
	}

	states.push(state);

}
