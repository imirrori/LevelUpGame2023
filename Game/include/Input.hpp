//
// Created by Dmitry Morozov on 30/3/23.
//

#ifndef LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_INPUT_HPP_
#define LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_INPUT_HPP_

#include "GL/glew.h"
#include "GLFW/glfw3.h"

class Input {
 public:
  static bool keys[1024];
  static bool keyUp[1024];
  static bool GetKey(int key);
  static bool GetKeyDown(int key);

};

#endif //LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_INPUT_HPP_
