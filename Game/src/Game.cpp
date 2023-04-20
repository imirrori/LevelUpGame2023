#include "Game.hpp"
#include "MenuStub.hpp"
#include "PlayerStub.hpp"

#include <fstream>
#include <iostream>

void Game::Run()
{
  Mainloop();
}

namespace {
constexpr std::string_view SettingFileName = "settings.ini";
}

void Game::Run()
{
  std::shared_ptr<IEntity> menu   = std::make_shared<MenuStub>(viz_);
  std::shared_ptr<IEntity> player = std::make_shared<PlayerStub>(viz_);

  while (viz_->Show({ menu, player }))
  {}
}

void Game::Init()
{
  window_ = viz_->GetWindowInstance();
}

Game::Game()
{
  std::ifstream inStream(SettingFileName.data());

  setting_ = std::make_shared<Settings::Settings>(inStream);

  viz_ = std::make_shared<Visual::Visualizer>(setting_);
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
