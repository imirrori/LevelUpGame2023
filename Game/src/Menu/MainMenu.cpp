//
// Created by Dmitry Morozov on 16/4/23.
//

#include "Menu/MainMenu.hpp"

MainMenu::MainMenu() {

  window_.create(VideoMode(2000, 1600), L"On create()", Style::Default);

  window_.setMouseCursorVisible(false);

  width_ = static_cast<float>(VideoMode::getDesktopMode().width);
  height_ = static_cast<float>(VideoMode::getDesktopMode().height);

  textLand_.loadFromFile("Resources/image/z1.png");

}



MainMenu::~MainMenu() = default;
