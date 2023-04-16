//
// Created by Dmitry Morozov on 13/4/23.
//

#ifndef MENU_H
#define MENU_H

#include "Entity/Entity.hpp"

#include <SFML/Graphics.hpp>

namespace game {

class GameMenu {
  float menu_X;
  float menu_Y;
  int menu_Step;
  int max_menu;
  int size_font;
  int mainMenuSelected;
  sf::Font font;
  std::vector<sf::Text> mainMenu;

  sf::Color menu_text_color = sf::Color::White;
  sf::Color chose_text_color = sf::Color::Yellow;
  sf::Color border_color = sf::Color::Black;

  void setInitText(sf::Text &text, const sf::String &str, float x_position, float y_position) const;

  sf::RenderWindow &menu_window_;
 public:

  GameMenu(sf::RenderWindow &window, float menu_x, float menu_y, int sizeFont, int step, std::vector<sf::String> &name);

  void draw();

  void MoveUp();

  void MoveDown();

  void setColorTextMenu(sf::Color menColor, sf::Color ChoColor, sf::Color BordColor);

  void AlignMenu(int position_x);

  int getSelectedMenuNumber() const {
	return mainMenuSelected;
  }

};

}
#endif //MENU_H
