#include "Game.hpp"

#include <fstream>

namespace {
constexpr std::string_view SettingFileName = "settings.ini";
}

void Game::Run()
{
  while (viz_->Show({}))
  {}
}

void Game::Init()
{}

Game::Game()
{
  std::ifstream inStream(SettingFileName.data());

  setting_ = std::make_shared<Settings::Settings>(inStream);

  viz_ = std::make_shared<Visual::Visualizer>(setting_);
}
