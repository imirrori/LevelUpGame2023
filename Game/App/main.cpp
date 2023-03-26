// dsd
#include "Game.hpp"
#include "Visualizer.hpp"

/*
    Dev. version
 */
int main(int argc, char **argv)
{
  Game game;
  game.Init(argc, argv);
  game.Run();
  return 0;
}
