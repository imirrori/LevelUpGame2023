//
// Created by Dmitry Morozov on 16/4/23.
//

#ifndef MARIO_GAME_SRC_MENU_MAINMENU_HPP_
#define MARIO_GAME_SRC_MENU_MAINMENU_HPP_

#include "Menu/Animator.hpp"
#include "Menu/AssetManager.hpp"
#include "Menu/GameMenu.hpp"
#include "Menu/MenuHandler.hpp"

#include <memory>
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
 public:

  MainMenu();

  ~MainMenu();

  void Run();

 private:
  std::vector<String> menuItems{L"Start", L"Options", L"About Game"};

  AssetManager assetManager_;
  RenderWindow window_;

  Sprite sprite;
  Sprite backgroundBlack;

  Texture textLand_;
  Texture textureBack;
  Texture textureWindow;

  std::unique_ptr<RectangleShape> homeCls_;
  std::unique_ptr<game::GameMenu> mainMenu_;
  std::unique_ptr<RectangleShape> background_;
  std::unique_ptr<Vector2i> spriteSize_;
  std::unique_ptr<Animator> animator;

  SoundBuffer buffer;
  SoundBuffer buf_return;

  Sound sound;
  Sound sound_return;

  Text Title_;

  TextFormat fText_;

  Music music;
  Music musicFire;

  Font font_;

  float alpha = 255.0f;
  float height_;
  float width_;

  int Init();

  static void InitText(Text &m_text, float x_pos, float y_pos, const String &str, TextFormat f_text);

};

#endif //MARIO_GAME_SRC_MENU_MAINMENU_HPP_
