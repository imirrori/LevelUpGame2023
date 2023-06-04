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
{}

void Player::onCollision(){

        for(int i = point_.y/block_pixel; i < (point_.y + player_pixel) / block_pixel; i++)
            for(int j = point_.x/block_pixel; j < (point_.x+ player_pixel) / block_pixel; j++){
                if(map->default_map_ == "b"){
                    if(vy_ > 0){
                        point_.y = i * block_pixel - player_pixel;
                    }
                    if(vy_ < 0){
                        point_.y = i * block_pixel + block_pixel;
                    }
                    if(vx_ > 0){
                        point_.x = i * block_pixel - player_pixel;
                    }
                    if(vx_ < 0){
                        point_.x = i * block_pixel + block_pixel;
                    }
                }

            }



}

void Player::onUpdate(std::chrono::nanoseconds duration)
{
  vx_ = vx_ + ax_ * std::chrono::duration_cast<std::chrono::milliseconds>(
    duration).count();

  if ((player_state_x == PLAYER_STATE_X::RUN_RIGHT) ||
      (player_state_x == PLAYER_STATE_X::STAND)) {
    vx_ = std::max(vx_, 0.);
  }

  if ((player_state_x == PLAYER_STATE_X::RUN_LEFT) ||
      (player_state_x == PLAYER_STATE_X::STAND)) {
    vx_ = std::min(vx_, 0.);
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



void Player::PressPlayerKey(KEY key)
{
  const double default_v = 0.003;
  const double default_a = 0.000003;

  switch (key)
  {
    case LEFT:
      player_state_x = PLAYER_STATE_X::RUN_LEFT;
      vx_            = -default_v * 1.4;
      ax_            = default_a;
      break;
    case RIGHT:
      player_state_x = PLAYER_STATE_X::RUN_RIGHT;
      vx_            = default_v * 1.4;
      ax_            = -default_a;
      break;
    case UP:

      if (player_state_y == PLAYER_STATE_Y::STAND) {
        player_state_y = PLAYER_STATE_Y::FLY;
        vy_            = default_v * 1.4;
        ay_            = -default_a;
      }
      break;
    case DOWN:

      if (player_state_y == PLAYER_STATE_Y::FLY) {
        player_state_y = PLAYER_STATE_Y::FALL;
        vy_            = -default_v;
        break;
      }
  }
}

Point Player::GetPlayerPoint()
{
  return point_;
}
