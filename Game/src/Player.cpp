#include "Player.hpp"

Player::Player(const std::shared_ptr<IPlayerVisualizer>& playerVizualizer)
  : _playerVizualizer(playerVizualizer)
{

}

void Player::OnInit()
{

}

void Player::OnUpdate(double deltaTime/* = 0.0 */)
{

}

void Player::OnRender()
{
  ShowPlayer(0, 0);
}

void Player::SetHealth(const int& health)
{
  _health = health;
}

bool Player::IsDead()
{
  if(_health <= 0)
    return true;
  return false;
}

void Player::Damage(const int& amount)
{
  if(IsDead())
  {
    _health = 0;
    Dead(); // or IsDead?
    return;
  }
  _health -= amount;
}

void Player::Dead()
{
  std::cout << "You are dead :(" << std::endl;
}
