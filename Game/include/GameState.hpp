//
// Created by Dmitry Morozov on 24/4/23.
//

#ifndef MARIO_GAME_SRC_GAMESTATE_HPP_
#define MARIO_GAME_SRC_GAMESTATE_HPP_

namespace State {

enum class GameState {

	GS_Loading,
	GS_Menu,
	GS_ScoreTable,
	GS_Running,
	GS_NextLevel,
	GS_Paused,
	GS_GameOver,
	GS_Quit

};

} // namespace State

#endif //MARIO_GAME_SRC_GAMESTATE_HPP_
