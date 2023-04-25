#ifndef GAME_HPP
#define GAME_HPP

#include "MainMenu.hpp"
#include "Settings.hpp"
#include "Visualizer.hpp"
#include "KeyManager.hpp"
#include "Map.hpp"
#include "PlayerStub.hpp"

#include <memory>

class Game {
public:

  Game();

  void Init();
  void Run();

private:

  std::shared_ptr<Settings::Settings>setting_;
  std::shared_ptr<KeyManager>keyManager_;
  std::shared_ptr<Visual::Visualizer>viz_;
  std::shared_ptr<MainMenu>menu_;
  std::shared_ptr<PlayerStub>player_;
  std::shared_ptr<Map>map_;

  std::vector<std::shared_ptr<IEntity> >showObjects_;
  std::function<void()>EscapeKey;
};

#endif // GAME_HPP
