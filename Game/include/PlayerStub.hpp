#ifndef PLAYERSTUB_HPP
#define PLAYERSTUB_HPP

#include "interface/IEntity.hpp"
#include "interface/IVizPlayer.hpp"

#include <memory>

class PlayerStub
  : public IEntity {
public:

  enum KEY
  {
    UP,
    DOWN,
    LEFT,
    RIGHT
  };

  PlayerStub(std::shared_ptr<Visual::IPlayer>playerViz)
    : playerViz_(std::move(playerViz))
    , x_(3)
    , y_(1)
  {}

  ~PlayerStub() override = default;

  void onUpdate() override {
  }

  void onRender() override    {
    playerViz_->ShowPlayer(x_, y_);
  }

  void onCollision() override {
  }

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

private:

  std::shared_ptr<Visual::IPlayer>playerViz_;
  int x_;
  int y_;
};

#endif // PLAYERSTUB_HPP
