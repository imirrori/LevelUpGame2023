#include "Game.hpp"
#include "Visualizer.hpp"

int main()
{
  Settings::GlobalSettings set;

  Game game(set);
  game.Init();
  game.Run();

  return 0;
}
