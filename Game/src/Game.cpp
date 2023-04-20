#include "Game.hpp"
#include <iostream>

void Game::Run()
{
  Mainloop();
}

void Game::Init()
{
  window_ = viz_->GetWindowInstance();
}

Game::Game()
{
  viz_ = std::make_shared<Visual::Visualizer>(setting);
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
