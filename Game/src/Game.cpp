#include "Game.hpp"

void Game::Run()
{
  viz_->Mainloop();
}

void Game::Init()
{}

Game::Game()
{
  viz_ = std::make_shared<Visual::Visualizer>(setting);
}
