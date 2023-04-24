//
// Created by Dmitry Morozov on 24/4/23.
//

#ifndef MARIO_GAME_SRC_GAMESTATE_HPP_
#define MARIO_GAME_SRC_GAMESTATE_HPP_

namespace State {

enum class GameState {

  GS_Running,
  GS_Paused,
  GS_Quit,
  GS_Win,
  GS_Lose,
  GS_Menu

};

} // namespace State

#endif //MARIO_GAME_SRC_GAMESTATE_HPP_
