#include "Game.hpp"
#include "PlayerStub.hpp"

#include <fstream>

namespace {
constexpr std::string_view SettingFileName = "settings.ini";
}

void Game::Run()
{
  std::shared_ptr<IEntity> player = std::make_shared<PlayerStub>(viz_);

  while (viz_->Show({ menu_, player }))
  {}
}

void Game::Init()
{}

Game::Game()
{
  std::ifstream inStream(SettingFileName.data());

  setting_ = std::make_shared<Settings::Settings>(inStream);

  viz_ = std::make_shared<Visual::Visualizer>(setting_);
  MainMenu a(std::static_pointer_cast<IMenu>(viz_));

  menu_ = std::make_shared<MainMenu>(viz_);

  menu_->AddSubMenu({ "start game", {} });
  menu_->AddSubMenu({ "load game", {} });
  menu_->AddSubMenu({ "end game", {} });
}
