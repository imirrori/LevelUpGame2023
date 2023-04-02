#ifndef GAME_HPP
#define GAME_HPP

#include "GlobalSettings.hpp"
#include "Visualizer.hpp"

#include <memory>

class Game {
public:

  Game();

  void Init();
  void Run();

private:

  Settings::GlobalSettings setting;
  std::shared_ptr<Visual::Visualizer>viz_;
};

#endif // GAME_HPP
