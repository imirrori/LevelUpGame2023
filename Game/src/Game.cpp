#include "Game.hpp"
#include "MenuStub.hpp"
#include "PlayerStub.hpp"
#include "MapStub.hpp"

#include <fstream>

namespace {
constexpr std::string_view SettingFileName =
  "D:/01_Projects/HomeWork/LEARN/LEARN/Level_3/GAME_level_up/Game/Game/configs/settings.ini";
}

void Game::Run()
{
  std::shared_ptr<IEntity> menu   = std::make_shared<MenuStub>(viz_);
  std::shared_ptr<IEntity> player = std::make_shared<PlayerStub>(viz_);
  std::shared_ptr<IMap>    map    = std::make_shared<MapStub>(viz_);

  while (viz_->Show({ menu, player }, map))
  {}
}

void Game::Init()
{
}

Game::Game()
{
  std::ifstream inStream(SettingFileName.data());

  setting_ = std::make_shared<Settings::Settings>(inStream);

  viz_ = std::make_shared<Visual::Visualizer>(setting_);
}
