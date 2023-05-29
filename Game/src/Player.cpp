#include "Player.hpp"

#include <limits>

Player::Player(std::shared_ptr<Visual::IPlayer>playerViz)
  : playerViz_(std::move(playerViz))
  , point_{0, 0}
  , vx_(0)
  , vy_(0)
  , ax_(0)
  , ay_(0)
  , player_state_x(PLAYER_STATE_X::STAND)
  , player_state_y(PLAYER_STATE_Y::STAND)
  , pre_point_(point_)
{}

void Player::onUpdate(std::chrono::nanoseconds duration)
{
  pre_point_ = point_;
  vx_        = vx_ + ax_ *
               std::chrono::duration_cast<std::chrono::milliseconds>(
    duration).count();

  if ((player_state_x == PLAYER_STATE_X::RUN_RIGHT) ||
      (player_state_x == PLAYER_STATE_X::STAND)) {
    vx_ = std::max(vx_, 0.);
  }

  if ((player_state_x == PLAYER_STATE_X::RUN_LEFT) ||
      (player_state_x == PLAYER_STATE_X::STAND)) {
    vx_ = std::min(vx_, 0.);
  }

  if ((player_state_y == PLAYER_STATE_Y::FALL) ||
      (player_state_y == PLAYER_STATE_Y::FALL_RIGHT) ||
      (player_state_y == PLAYER_STATE_Y::FALL_LEFT))
  {
    if (point_.y == 0)
    {
      player_state_y = PLAYER_STATE_Y::STAND;
    }
  }

  if (vx_ == 0) {
    player_state_x = PLAYER_STATE_X::STAND;
    ax_            = 0;
  }

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
    point_.y       = 0;
    player_state_y = PLAYER_STATE_Y::STAND;
  }
}

void Player::onRender()
{
  playerViz_->ShowPlayer(point_, player_state_x, player_state_y);
}

void Player::onCollision() {
}

void Player::PressPlayerKey(KEY key)
{
  const double default_v = 0.003;
  const double default_a = 0.000003;

  switch (key)
  {
    case LEFT:

      if (player_state_y == PLAYER_STATE_Y::FLY_RIGHT)
      {
        player_state_y = PLAYER_STATE_Y::FLY_LEFT;
      }

      if (player_state_y == PLAYER_STATE_Y::FLY_LEFT)
      {
        player_state_y = PLAYER_STATE_Y::FLY_LEFT;
      }

      if (player_state_y == PLAYER_STATE_Y::FALL_LEFT)
      {
        player_state_y = PLAYER_STATE_Y::FALL_LEFT;
      }

      if (player_state_y == PLAYER_STATE_Y::FALL_RIGHT)
      {
        player_state_y = PLAYER_STATE_Y::FALL_LEFT;
      }

      if (point_.y == 0)
      {
        player_state_x = PLAYER_STATE_X::RUN_LEFT;
      }
      vx_ = -default_v * 1.4;
      ax_ = default_a;

      break;
    case RIGHT:

      if (player_state_y == PLAYER_STATE_Y::FLY_LEFT)
      {
        player_state_y = PLAYER_STATE_Y::FLY_RIGHT;
      }

      if (player_state_y == PLAYER_STATE_Y::FLY_RIGHT)
      {
        player_state_y = PLAYER_STATE_Y::FLY_RIGHT;
      }

      if (player_state_y == PLAYER_STATE_Y::STAND)
      {
        player_state_x = PLAYER_STATE_X::RUN_RIGHT;
      }

      if (player_state_x == PLAYER_STATE_X::RUN_LEFT)
      {
        player_state_x = PLAYER_STATE_X::RUN_RIGHT;
      }

      if (player_state_y == PLAYER_STATE_Y::FALL_LEFT)
      {
        player_state_y = PLAYER_STATE_Y::FALL_RIGHT;
      }

      if (player_state_y == PLAYER_STATE_Y::FALL_RIGHT)
      {
        player_state_y = PLAYER_STATE_Y::FALL_RIGHT;
      }

      if (point_.y == 0)
      {
        player_state_x = PLAYER_STATE_X::RUN_RIGHT;
      }
      vx_ = default_v * 1.4;
      ax_ = -default_a;
      break;
    case UP:

      if (player_state_y == PLAYER_STATE_Y::STAND) {
        if (point_.x >= pre_point_.x)
        {
          player_state_y = PLAYER_STATE_Y::FLY_RIGHT;
        }

        if (point_.x < pre_point_.x)
        {
          player_state_y = PLAYER_STATE_Y::FLY_LEFT;
        }
        vy_ = default_v * 1.4;
        ay_ = -default_a;
      }
      break;
    case DOWN:

      if ((point_.x > pre_point_.x) && (point_.y != 0))
      {
        player_state_y = PLAYER_STATE_Y::FALL_RIGHT;
      }

      if ((point_.x < pre_point_.x) && (point_.y != 0))
      {
        player_state_y = PLAYER_STATE_Y::FALL_LEFT;
      }

      if ((point_.x == pre_point_.x) && (point_.y != 0))
      {
        player_state_y = PLAYER_STATE_Y::FALL;
      }

      vy_ = -default_v;
      break;
  }
}

Point Player::GetPlayerPoint()
{
  return point_;
}
