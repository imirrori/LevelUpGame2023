#include "Player.hpp"

//void Player::ShowPlayer(const int& x, const int& y)
//{
//  _posX = x;
//  _posY = y;
//}

void Player::OnInit()
{

}

void Player::OnUpdate(double deltaTime/* = 0.0 */)
{

}

void Player::OnRender()
{

}

void Player::SetHealth(const int& health)
{
  _health = health;
}

void Player::Damage(const int& amount)
{
  if(_health <= 0)
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
