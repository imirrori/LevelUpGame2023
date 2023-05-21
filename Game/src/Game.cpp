#include "Game.hpp"
#include "PlayerStub.hpp"
#include "Score.hpp"

#include <fstream>
#include <optional>

namespace {
constexpr std::string_view SettingFileName = "settings.ini";
}

std::array<std::unique_ptr<Game::IState>,
           Game::IState::STATES::COUNT> Game::states_ =
{};

void Game::Run()
{
  while (viz_->Show(state_->GetShowObjects()))
  {
    std::vector<KeyManager::Key> keysDown = keyManager_->GetKeysDown();

    for (const auto& key: keysDown) {
      state_ = state_->ProcessingKey(key);
      keyManager_->KeyAction(key.key,
                             key.scancode,
                             KeyManager::RELEASE,
                             key.mods);
    }
    score_->AddScore();
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
  score_      = std::make_shared<Score>(viz_, player_, map_);

  states_[IState::BEGIN_SATE] = std::make_unique<BeginState>(menu_,
                                                             std::vector<std::shared_ptr<IEntity> >{ menu_ });
  states_[IState::PLAY_SATE] = std::make_unique<PlayState>(player_,
                                                           std::vector<std::shared_ptr<IEntity> >{ map_,
                                                                                                   player_,
                                                                                                   score_ });
  state_ = states_[IState::BEGIN_SATE].get();

  auto endGame = []() {
                   exit(0);
                   return false;
                 };
  auto startGame = []()
                   {
                     return true;
                   };
  auto loadGame = []() {
                    return false;
                  };

  menu_->AddSubMenu({ "Start game", startGame });
  menu_->AddSubMenu({ "Load game", loadGame });
  menu_->AddSubMenu({ "End game", endGame });
}

Game::Game()
{}
