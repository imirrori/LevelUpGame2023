//
// Created by Dmitry Morozov on 27/4/23.
//

#ifndef MARIO_GAME_INCLUDE_INTERFACE_IPROCESSINPUT_HPP_
#define MARIO_GAME_INCLUDE_INTERFACE_IPROCESSINPUT_HPP_

#include "GLFW/glfw3.h"

class IProcessInput {

 public:

  virtual void processInput(GLFWwindow *window) = 0;

};

#endif //MARIO_GAME_INCLUDE_INTERFACE_IPROCESSINPUT_HPP_
