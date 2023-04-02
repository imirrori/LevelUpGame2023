#include "Game.hpp"

void Game::Run()
{
}

void Game::Init()
{
  _viz->make_window();
}

Game::Game()
{
  _viz = std::make_shared<Visual::Visualizer>(Visual::Visualizer());
}
