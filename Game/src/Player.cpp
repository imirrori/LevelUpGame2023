#include "Player.hpp"

Player::Player(int x, int y, std::shared_ptr<IPlayer>viz)
  : x_(x)
  , y_(y)
  , viz_(std::move(viz))
{}

void Player::show() const
{
  viz_->ShowPlayer(x_, y_);
}
