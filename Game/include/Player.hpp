#ifndef PLAYER_H
#define PLAYER_H

#include "interface/IEntity.hpp"
#include "interface/IVizPlayer.hpp"

#include <memory>

class Player
  : public IEntity {
public:

  enum KEY
  {
    UP,
    DOWN,
    LEFT,
    RIGHT
  };

  Player(std::shared_ptr<Visual::IPlayer>playerViz)
    : playerViz_(std::move(playerViz))
    , x_(0)
    , y_(1)
  {}

  ~Player() override = default;

  void onUpdate(std::chrono::duration<uint64_t>) override {}

  void onRender() override    {
    playerViz_->ShowPlayer(x_, y_);
  }

  void onCollision() override {}

  void PressPlayerKey(KEY key)
  {
    switch (key)
    {
      case LEFT:

        if (x_ > 0) --x_;
        break;
      case RIGHT:
        ++x_;
        break;
      case UP:

        if (y_ < 8) ++y_;
        break;
      case DOWN:

        if (y_ > 1) --y_;
        break;
    }
  }

  int GetPlayerX_()
  {
    return x_;
  }

  int GetPlayerY_()
  {
    return y_;
  }

private:

  std::shared_ptr<Visual::IPlayer>playerViz_;
  int x_;
  int y_;
};
#endif // PLAYER_H
