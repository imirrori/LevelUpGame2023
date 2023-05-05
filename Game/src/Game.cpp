#include "Game.hpp"
#include "PlayerStub.hpp"

#include <fstream>
#include <iostream>
#include <optional>

namespace {
}

std::array<std::unique_ptr<Game::IState>,
           Game::IState::STATES::COUNT> Game::states_ =
{};

void Game::Run()
{
  while (viz_->Show(state_->GetShowObjects()))
  {
    std::vector<KeyManager::Key> keysDown = keyManager_->GetKeysDown();

  while (viz_->Show({ menu, player }))
  {
    Mainloop();
    for (const auto& key: keysDown) {
      state_ = state_->ProcessingKey(key);
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

  setting_  = std::make_shared<Settings::Settings>(inStream);
  //viz_      = std::make_shared<Visual::Visualizer>(setting_);
  window_   = viz_->GetWindowInstance();
  keyManager_ = std::make_shared<KeyManager>();
  viz_        = std::make_shared<Visual::Visualizer>(setting_, keyManager_);
  player_     = std::make_shared<PlayerStub>(viz_);
  menu_       = std::make_shared<MainMenu>(viz_);
  map_        = std::make_shared<Map>(viz_);

  states_[IState::BEGIN_SATE] = std::make_unique<BeginState>(menu_,
                                                             std::vector<std::shared_ptr<IEntity> >{ menu_ });
  states_[IState::PLAY_SATE] = std::make_unique<PlayState>(player_,
                                                           std::vector<std::shared_ptr<IEntity> >{ map_,
                                                                                                   player_ });
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

  menu_->AddSubMenu({ "start game", startGame });
  menu_->AddSubMenu({ "load game", loadGame });
  menu_->AddSubMenu({ "end game", endGame });
}

void Game::Action()
{
  std::lock_guard<std::mutex> _(mutex_);

  if(glfwGetKey(window_, GLFW_KEY_LEFT) == GLFW_PRESS)
  {
    // Moving right
    std::cout << "moving right" << std::endl;
  }
  if(glfwGetKey(window_, GLFW_KEY_RIGHT) == GLFW_PRESS)
  {
    // moving left
    std::cout << "moving left" << std::endl;
  }
  if(glfwGetKey(window_, GLFW_KEY_SPACE) == GLFW_PRESS)
  {
    // Jump
    std::cout << "jump" << std::endl;
  }
}

void Game::Render()
{
  /* Render here */
  glClear(GL_COLOR_BUFFER_BIT);

  viz_->OnRender();

  /* Swap front and back buffers */
  glfwSwapBuffers(window_);

  /* Poll for and process events */
  glfwPollEvents();
}

void Game::Mainloop()
{
  while (!glfwWindowShouldClose(window_))
  {
    std::thread threadAction(&Game::Action, this);
    if(threadAction.joinable())
      threadAction.join();

    Render();
  }
}

Game::Game()
{}
