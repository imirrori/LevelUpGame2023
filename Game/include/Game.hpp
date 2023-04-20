#ifndef GAME_HPP
#define GAME_HPP

#include "Settings.hpp"
#include "Visualizer.hpp"
#include "Player.hpp"

#include <memory>
#include <thread>
#include <mutex>

class Game {
public:
  Game();

  void Init();
  void Run();

  void Mainloop();

  void Action();
  void Render();

private:
  Settings::GlobalSettings setting;
  std::shared_ptr<Settings::Settings>setting_;
  std::shared_ptr<Visual::Visualizer>viz_;
  GLFWwindow *window_;
  std::mutex mutex_;
};

#endif // GAME_HPP
