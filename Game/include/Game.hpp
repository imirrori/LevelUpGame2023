#ifndef GAME_HPP
#define GAME_HPP

#include "Visualizer.hpp"
#include <memory>

class Game {
private:

  std::shared_ptr<Visual::Visualizer>_viz;

public:

  void Init();

  void Run();

  Game();
};

#endif // GAME_HPP
