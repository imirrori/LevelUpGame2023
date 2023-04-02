#include "Game.hpp"

Game::Game(const Settings::GlobalSettings& setting)
  : viz_{std::make_shared<Visual::Visualizer>(setting)}
  , player_(1, 1, viz_)
  , menu_(viz_, "name")
{}

void Game::Run()
{
  while (viz_->Show(player_, menu_))
  {}
}

void Game::Init()
{
}
