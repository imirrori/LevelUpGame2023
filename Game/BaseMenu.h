//
// Created by Arina on 07.04.2023.
//

#ifndef LEVELUPGAME2023_GAME_BASEMENU_H_
#define LEVELUPGAME2023_GAME_BASEMENU_H_
enum class StateType
{
  MAIN_MENU, LEVEL_SELECT, GAME
};

class BaseState
{
 public:
  BaseState();
   ~BaseState();
  virtual void Paint() = 0;
  StateType GetType();
 private:
  StateType m_StateType;

};

#endif //LEVELUPGAME2023_GAME_BASEMENU_H_
