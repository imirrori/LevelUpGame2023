#include "Game.h"

void Game::Run()
{
    _viz->mainloop();
}

void Game::Init()
{
    _viz->init();
}

Game::Game()
{
    _viz = std::make_shared<Visual::Visualizer>();
}
