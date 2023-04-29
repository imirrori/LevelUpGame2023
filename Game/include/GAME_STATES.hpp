//
// Created by Dmitry Morozov on 24/4/23.
//

#ifndef MARIO_GAME_SRC_GAMESTATE_HPP_
#define MARIO_GAME_SRC_GAMESTATE_HPP_

#include <iostream>
#include <map>
#include <stack>

namespace State {

enum class GAME_STATES {

	GS_Loading = 1,
	GS_Menu,
	GS_ScoreTable,
	GS_Running, // State 4
	GS_Jumping, // State 5
	GS_NextLevel,
	GS_Paused,
	GS_GameOver,
	GS_Quit,
	GS_MovingLeft, // State 10
	GS_MovingRight, // State 11
	GS_None // State 12

};

//std::map<GAME_STATES, std::string> GAME_STATES_STR = {
//	{GAME_STATES::GS_Loading, "GS_Loading"},
//	{GAME_STATES::GS_Menu, "GS_Menu"},
//	{GAME_STATES::GS_ScoreTable, "GS_ScoreTable"},
//	{GAME_STATES::GS_Running, "GS_Running"},
//	{GAME_STATES::GS_Jumping, "GS_Jumping"},
//	{GAME_STATES::GS_NextLevel, "GS_NextLevel"},
//	{GAME_STATES::GS_Paused, "GS_Paused"},
//	{GAME_STATES::GS_GameOver, "GS_GameOver"},
//	{GAME_STATES::GS_Quit, "GS_Quit"},
//	{GAME_STATES::GS_MovingLeft, "GS_MovingLeft"},
//	{GAME_STATES::GS_MovingRight, "GS_MovingRight"},
//	{GAME_STATES::GS_None, "GS_None"}
//};
//
//void printGameState(GAME_STATES state) {
//
//	std::cout << "Current state: " << GAME_STATES_STR[state] << std::endl;
//
//}

} // namespace State

#endif //MARIO_GAME_SRC_GAMESTATE_HPP_
