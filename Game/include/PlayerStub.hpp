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
    , x_(1)
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

        if (x_ > 0) x_ -= 0.5;
        break;
      case RIGHT:

        if (x_ < 200) x_ += 0.5;
        break;
      case UP:

        if (y_ < 7) y_ += 0.5;
        break;
      case DOWN:

        if (y_ > 1) y_ -= 0.5;
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
  double x_;
  double y_;
};
#endif // PLAYERSTUB_HPP
