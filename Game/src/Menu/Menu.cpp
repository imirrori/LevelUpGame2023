//
// Created by Dmitry Morozov on 13/4/23.
//

#include "Menu/Menu.hpp"

#include <string>


MenuList::MenuList() {

  vTag = "Menu";

}

MenuList::MenuList(std::string tag) {

  vTag = std::move(tag);

}

void MenuList::addItem(float x_, float y_, bool is_slider, const std::string &name_, void(*function_)()) {

  items.emplace_back(x_, y_, is_slider, name_, function_);

}