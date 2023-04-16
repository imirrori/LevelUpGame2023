#ifndef GAME_HPP
#define GAME_HPP

#include "Settings.hpp"
#include "Visualizer.hpp"

#include <memory>

class Game {
public:

  Game();

  void Init();
  void Run();

private:

  std::shared_ptr<Settings::Settings>setting_;
  std::shared_ptr<Visual::Visualizer>viz_;
};

#endif // GAME_HPP
