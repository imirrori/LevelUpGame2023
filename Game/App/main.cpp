
#include "Game.hpp"

#include "GL/glew.h"

int main() {

  constexpr unsigned int width = 1920, height = 1080;

  Game game(width, height);

  game.Run();

  return 0;
}
