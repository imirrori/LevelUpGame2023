//
// Created by Dmitry Morozov on 13/4/23.
//

#include "Menu/GameMenu.hpp"

#include <vector>

void game::GameMenu::setInitText(sf::Text &text, const sf::String &str, float x_position, float y_position) const {

  text.setFont(font);
  text.setFillColor(menu_text_color);
  text.setString(str);
  text.setCharacterSize(size_font);
  text.setPosition(x_position, y_position);
  text.setOutlineThickness(3);
  text.setOutlineColor(border_color);

}

void game::GameMenu::AlignMenu(int position_x) {

  float reference_x = 0;

  for (int i = 0; i < max_menu; i++) {

	switch (position_x) {

	  case 0: reference_x = 0;
		break;

	  case 1: reference_x = mainMenu[i].getLocalBounds().width;
		break;

	  case 2: reference_x = mainMenu[i].getLocalBounds().width/2;
		break;

	  default:break;

	}

	mainMenu[i].setPosition(mainMenu[i].getPosition().x - reference_x, mainMenu[i].getPosition().y);
  }

}

game::GameMenu::GameMenu(sf::RenderWindow &window,
						 float menu_x,
						 float menu_y,
						 int sizeFont,
						 int step,
						 std::vector<sf::String> &name)
	: menu_X(menu_x),
	  menu_Y(menu_y),
	  menu_Step(step),
	  max_menu(static_cast<int>(name.size())),
	  size_font(sizeFont),
	  mainMenu(name.size()),

	  menu_window_(window) {

  if (!font.loadFromFile("font/troika.otf")) exit(32);

  for (int i = 0, y_position = static_cast<int>(menu_Y); i < max_menu; i++, y_position += menu_Step) {

	setInitText(mainMenu[i], name[i], menu_X, static_cast<float>(y_position));

  }

  mainMenuSelected = 0;
  mainMenu[mainMenuSelected].setFillColor(chose_text_color);

}

void game::GameMenu::MoveUp() {

  mainMenuSelected--;

  if (mainMenuSelected >= 0) {

	mainMenu[mainMenuSelected].setFillColor(chose_text_color);
	mainMenu[mainMenuSelected + 1].setFillColor(menu_text_color);

  } else {

	mainMenu[0].setFillColor(menu_text_color);
	mainMenuSelected = max_menu - 1;
	mainMenu[mainMenuSelected].setFillColor(chose_text_color);

  }

}

void game::GameMenu::MoveDown() {

  mainMenuSelected++;

  if (mainMenuSelected < max_menu) {

	mainMenu[mainMenuSelected - 1].setFillColor(menu_text_color);
	mainMenu[mainMenuSelected].setFillColor(chose_text_color);

  } else {

	mainMenu[max_menu - 1].setFillColor(menu_text_color);
	mainMenuSelected = 0;
	mainMenu[mainMenuSelected].setFillColor(chose_text_color);

  }

}

void game::GameMenu::draw() {

  for (int i = 0; i < max_menu; i++) menu_window_.draw(mainMenu[i]);

}

void game::GameMenu::setColorTextMenu(sf::Color menColor, sf::Color ChoColor, sf::Color BordColor) {

  menu_text_color = menColor;
  chose_text_color = ChoColor;
  border_color = BordColor;

  for (int i = 0; i < max_menu; i++) {

	mainMenu[i].setFillColor(menu_text_color);
	mainMenu[i].setOutlineColor(border_color);

  }

  mainMenu[mainMenuSelected].setFillColor(chose_text_color);

}
