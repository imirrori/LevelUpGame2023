
#include "Game.hpp"

#include <filesystem>
#include <iostream>

int main() {

  constexpr unsigned int width = 1920, height = 1080;

  std::cout << "Current path is " << std::filesystem::current_path() << std::endl; // (1)

  Game game(width, height);

  game.Run();

  return 0;
}
