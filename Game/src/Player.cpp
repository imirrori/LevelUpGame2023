#include "Player.hpp"


Player::Player(std::shared_ptr<Visual::IPlayer>playerViz)
  : playerViz_(std::move(playerViz))
  , point_{0, 0}
  , vx_(0)
  , vy_(0)
  , ax_(0)
  , ay_(0)
{}

void Player::onUpdate(std::chrono::nanoseconds duration)
{
  vx_ = vx_ + ax_ * std::chrono::duration_cast<std::chrono::milliseconds>(
    duration).count();
  vy_ = vy_ + ay_ * std::chrono::duration_cast<std::chrono::milliseconds>(
    duration).count();

  point_.x = point_.x + vx_ *
             std::chrono::duration_cast<std::chrono::milliseconds>(
    duration).count();
  point_.y = point_.y + vy_ *
             std::chrono::duration_cast<std::chrono::milliseconds>(
    duration).count();

  if (point_.x < 0) {
    point_.x = 0;
  }

  if (point_.y < 0) {
    point_.y = 0;
  }
}

void Player::onRender()
{
  playerViz_->ShowPlayer(point_);
}

void Player::onCollision() {}

void Player::PressPlayerKey(KEY key)
{
  const double default_v = 0.003;
  const double default_a = 0.000003;

  switch (key)
  {
    case LEFT:
      vx_ = -default_v;
      break;
    case RIGHT:
      vx_ = default_v;
      break;
    case UP:
      vy_ = default_v * 1.4;
      ay_ = -default_a;
      break;
    case DOWN:
      vy_ = -default_v;
      break;
  }
}

Point Player::GetPlayerPoint()
{
  return point_;
}
