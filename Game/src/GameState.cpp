//
// Created by Dmitry Morozov on 27/4/23.
//

#include "GameState.hpp"
#include "GAME_STATES.hpp"

using STATE = State::GAME_STATES;

std::stack<State::GAME_STATES> GameState::states_;

GameState::GameState() {

	states_.push(State::GAME_STATES::GS_Loading);

}

void GameState::pushState(STATE state) {

	states_.push(state);

}

void GameState::popState() {

	states_.pop();

}

void GameState::changeState(STATE state) {

	if (not states_.empty()) {
		states_.pop();
	}

	states_.push(state);

}

State::GAME_STATES GameState::peekState() {

	if (not states_.empty()) {
		return states_.top();
	}

	return State::GAME_STATES::GS_None;

}
void GameState::swapState(STATE state) {

	if (not states_.empty()) {
		states_.pop();
	}

	states_.push(state);

}
bool GameState::isEmpty() {

	return states_.empty();
}
