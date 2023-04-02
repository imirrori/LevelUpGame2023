#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "GlobalSettings.hpp"
#include "interface/IPlayer.hpp"

#include <memory>

class Player {
public:

  Player(int                     x,
         int                     y,
         std::shared_ptr<IPlayer>viz);

  void show() const;

private:

  int x_;
  int y_;
  std::shared_ptr<IPlayer>viz_;
};
#endif // PLAYER_HPP
