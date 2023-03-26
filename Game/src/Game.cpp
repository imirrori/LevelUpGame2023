#include "Game.hpp"

void Game::Run()
{
  _viz->mainloop();
}

void Game::Init(int& argc, char **argv)
{
  _viz->init(argc, argv);
}

Game::Game()
{
  _viz = std::make_shared<Visual::Visualizer>(Visual::Visualizer());
}
