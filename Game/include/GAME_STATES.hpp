//
// Created by Dmitry Morozov on 24/4/23.
//

#ifndef MARIO_GAME_SRC_GAMESTATE_HPP_
#define MARIO_GAME_SRC_GAMESTATE_HPP_

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


} // namespace State

#endif //MARIO_GAME_SRC_GAMESTATE_HPP_
