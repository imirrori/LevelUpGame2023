//
// Created by Dmitry Morozov on 13/4/23.
//

#include "Menu/Menu.hpp"

#include <string>

MenuItem::MenuItem() {

  boolValue = nullptr;
  handler_ = nullptr;

}

MenuItem::MenuItem(float x_, float y_, bool is_slider, std::string tag_, void(*function)()) {
  x = x_;
  y = y_;
  w = 0;
  h = 0;

  boolValue = nullptr;
  floatValue = nullptr;

  tag = std::move(tag_);

  handler_ = function;
  isSlider = is_slider;
}

MenuList::MenuList() {

  vTag = "Menu";

}

MenuList::MenuList(std::string tag) {

  vTag = std::move(tag);

}

void MenuList::addItem(float x_, float y_, bool is_slider, const std::string &name_, void(*function_)()) {

  items.emplace_back(x_, y_, is_slider, name_, function_);

}