#ifndef GAME_HPP
#define GAME_HPP

#include "GlobalSettings.hpp"
#include "Map.hpp"
#include "Menu.hpp"
#include "Player.hpp"
#include "Visualizer.hpp"

#include <memory>

class Game {
public:

  Game(const Settings::GlobalSettings& setting);

  void Init();
  void Run();

private:

  Settings::GlobalSettings setting;
  std::shared_ptr<Visual::Visualizer>viz_;
  Player player_;
  Menu menu_;

  //  Map map_;
};

#endif // GAME_HPP
