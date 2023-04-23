#include "Game.hpp"
#include "PlayerStub.hpp"

#include <fstream>
#include <optional>

namespace {
constexpr std::string_view SettingFileName = "settings.ini";
}

void Game::Run()
{
  std::shared_ptr<IEntity> player = std::make_shared<PlayerStub>(viz_);

  while (viz_->Show({ menu_, player }))
  {
    std::vector<KeyManager::Key> keysDown = keyManager_->GetKeysDown();

    for (const auto& key: keysDown) {
      switch (key.key) {
        case 264: // DOWN
          menu_->PressKey(MainMenu::DOWN);
          break;
        case 265: // UP
          menu_->PressKey(MainMenu::UP);
          break;
        case 257: // ENTER
          menu_->PressKey(MainMenu::ENTER);
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
{}

Game::Game()
{
  std::ifstream inStream(SettingFileName.data());

  setting_    = std::make_shared<Settings::Settings>(inStream);
  keyManager_ = std::make_shared<KeyManager>();
  viz_        = std::make_shared<Visual::Visualizer>(setting_, keyManager_);
  MainMenu a(std::static_pointer_cast<IMenu>(viz_));

  menu_ = std::make_shared<MainMenu>(viz_);

  menu_->AddSubMenu({ "start game", {} });
  menu_->AddSubMenu({ "load game", {} });
  menu_->AddSubMenu({ "end game", []() {
                        exit(0);
                      } });
}
