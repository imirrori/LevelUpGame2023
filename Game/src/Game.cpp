#include "Game.hpp"
#include "PlayerStub.hpp"

#include <fstream>
#include <optional>

namespace {
constexpr std::string_view SettingFileName = "settings.ini";
}

void Game::Run()
{
  while (viz_->Show(showObjects_))
  {
    std::vector<KeyManager::Key> keysDown = keyManager_->GetKeysDown();

    for (const auto& key: keysDown) {
      switch (key.key) {
        case 264: // DOWN
          menu_->PressKey(MainMenu::DOWN);
          player_->PressPlayerKey(PlayerStub::DOWN);
          break;
        case 265: // UP
          menu_->PressKey(MainMenu::UP);
          player_->PressPlayerKey(PlayerStub::UP);
          break;
        case 262: // Player RIGHT
          player_->PressPlayerKey(PlayerStub::RIGHT);
          break;
        case 263: // Player LEFT
          player_->PressPlayerKey(PlayerStub::LEFT);
          break;
        case 257: // ENTER
          menu_->PressKey(MainMenu::ENTER);
          break;
        case 256: // ESC
          EscapeKey();
          break;
      }
      keyManager_->KeyAction(key.key,
                             key.scancode,
                             KeyManager::RELEASE,
                             key.mods);
    }
  }
}

void Game::Init()
{
  std::ifstream inStream(SettingFileName.data());

  setting_    = std::make_shared<Settings::Settings>(inStream);
  keyManager_ = std::make_shared<KeyManager>();
  viz_        = std::make_shared<Visual::Visualizer>(setting_, keyManager_);
  player_     = std::make_shared<PlayerStub>(viz_);
  menu_       = std::make_shared<MainMenu>(viz_);
  map_        = std::make_shared<Map>(viz_);

  auto endGame = []() {
                   exit(0);
                 };
  auto startGame = [this, endGame]()
                   {
                     std::vector<std::shared_ptr<IEntity> > newShow;

                     newShow.push_back(map_);
                     newShow.push_back(player_);
                     showObjects_.swap(newShow);

                     EscapeKey = [this, endGame]()
                                 {
                                   std::vector<std::shared_ptr<IEntity> >
                                   newShow;

                                   newShow.push_back(menu_);
                                   showObjects_.swap(newShow);
                                   EscapeKey = endGame;
                                 };
                   };
  auto loadGame = []() {};

  EscapeKey = endGame;

  menu_->AddSubMenu({ "start game", startGame });
  menu_->AddSubMenu({ "load game", loadGame });
  menu_->AddSubMenu({ "end game", endGame });

  showObjects_.push_back(menu_);
}

Game::Game()
{}
