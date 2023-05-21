#include "Player.hpp"


Player::Player(std::shared_ptr<Visual::IPlayer>playerViz)
  : playerViz_(std::move(playerViz))
  , x_(0)
  , y_(1)
  , vx_(0)
  , vy_(0)
  , ax_(0)
  , ay_(0)
{}

void Player::onUpdate(std::chrono::duration<uint64_t>) {}

void Player::onRender() {
  playerViz_->ShowPlayer(x_, y_);
}

void Player::onCollision() {}

void Player::PressPlayerKey(KEY key)
{
  switch (key)
  {
    case LEFT:
      vx_ = -1;
      break;
    case RIGHT:
      vx_ = +1;
      break;
    case UP:
      vy_ = +1;
      break;
    case DOWN:
      vy_ = -1;
      break;
  }
}

int Player::GetPlayerX_()
{
  return x_;
}

int Player::GetPlayerY_()
{
  return y_;
}
