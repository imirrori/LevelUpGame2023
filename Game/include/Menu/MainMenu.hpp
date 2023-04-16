//
// Created by Dmitry Morozov on 16/4/23.
//

#ifndef MARIO_GAME_SRC_MENU_MAINMENU_HPP_
#define MARIO_GAME_SRC_MENU_MAINMENU_HPP_

#include "Menu/Animator.hpp"
#include"Menu/GameMenu.hpp"

#include<SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;

struct TextFormat {

  int fontSize = 60;
  float bord = 0.0f;

  Color menu_text_color = Color::White;
  Color border_color = Color::Black;

};



class MainMenu {

};

#endif //MARIO_GAME_SRC_MENU_MAINMENU_HPP_
