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
	GS_Running,
	GS_Jumping,
	GS_NextLevel,
	GS_Paused,
	GS_GameOver,
	GS_Quit,
	GS_MovingLeft,
	GS_MovingRight,
	GS_None
};


} // namespace State

#endif //MARIO_GAME_SRC_GAMESTATE_HPP_
