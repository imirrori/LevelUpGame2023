#include "Game.hpp"
#include "MenuStub.hpp"

#include <fstream>

namespace {
constexpr std::string_view SettingFileName = "settings.ini";
}

void Game::Run()
{
  std::shared_ptr<IEntity> menu = std::make_shared<MenuStub>(viz_);

  while (viz_->Show({ menu }))
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
