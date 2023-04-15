//
// Created by Dmitry Morozov on 13/4/23.
//

#ifndef MENU_H
#define MENU_H

#include "Entity/Entity.hpp"

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

  float x{}, y{}, w{}, h{};

  std::string tag;
  bool *boolValue;
  bool isSlider{};
  float *floatValue{};

  void (*handler_)();

};

class MenuList : public Entity {

 public:

  MenuList();
  MenuList(std::string tag_);

  ~MenuList() override = default;

 private:

  std::vector<MenuItem> items;

  std::string name;

  void addItem(float x_, float y_, bool is_slider, const std::string &name_, void(*function_)());
};

#endif //MENU_H
