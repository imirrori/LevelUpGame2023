#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "IPlayer.hpp"
#include "IPlayerVisualizer.hpp"
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>

class Player : public IPlayer
{
public:
  Player(const std::shared_ptr<IPlayerVisualizer>& playerVizualizer);

  void OnInit()                         override;
  void OnUpdate(double deltaTime = 0.0) override;
  void OnRender()                       override;

  void SetHealth(const int& health);
  void Damage(const int& amount);
  void Dead();
  bool IsDead();

  int GetHealth() const { return _health; }

private:
  int    _health = 100.0;
  double _posX   = 0.0;
  double _posY   = 0.0;
  double _speed  = 0.1;
  std::shared_ptr<IPlayerVisualizer> _playerVizualizer;
};

#endif // PLAYER_HPP
