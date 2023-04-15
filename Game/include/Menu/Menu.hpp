//
// Created by Dmitry Morozov on 13/4/23.
//

#ifndef MENU_H
#define MENU_H

#include "Entity/Entity.hpp"

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

constexpr std::string BoolToString(bool b) {
  return b ? "true" : "false";
}

class MenuItem {
 public:

  MenuItem();
  MenuItem(float x_, float y_, bool is_slider, std::string name_, void(*function)());
  ~MenuItem() = default;

 private:

  void (*handler_)();

};

class MenuList : public Entity {

 public:

  MenuList();

  ~MenuList() override = default;

  MenuList(sf::RenderWindow &window, float menux, float menuy, int sizeFont, int step, std::vector<sf::String> &name);

  void draw();                                     // ������ ����

  void MoveUp();                                   // ����������� ������ ���� �����

  void MoveDown();                                 // ����������� ������ ���� ����

  // ���� ��������� �������� ����
  void setColorTextMenu(sf::Color menColor, sf::Color ChoColor, sf::Color BordColor);

  void AlignMenu(int posx);       // ������������ ��������� ���� (�� ������ �� ������� �� ������)

  int getSelectedMenuNumber() const     // ���������� ����� ��������� ��������
  {
	return mainMenuSelected;
  }

 private:

  float menu_X;
  float menu_Y;

  int menu_step_;
  int max_menu_;
  int font_size_;
  int mainMenuSelected;

  sf::Font font;

  std::vector<sf::Text> mainMenu;

  sf::Color menu_text_color = sf::Color::White;
  sf::Color chose_text_color = sf::Color::Yellow;
  sf::Color border_color = sf::Color::Black;

  void setInitText(sf::Text &text, const sf::String &str, float xpos, float ypos) const;

  sf::RenderWindow &mywindow;

};

#endif //MENU_H
