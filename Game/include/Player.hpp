#ifndef PLAYER_H
#define PLAYER_H

#include "interface/IEntity.hpp"
#include "interface/IVizPlayer.hpp"

#include <memory>

class Player
  : public IEntity {
public:

  enum KEY
  {
    UP,
    DOWN,
    LEFT,
    RIGHT
  };

  Player(std::shared_ptr<Visual::IPlayer>playerViz);
  ~Player() override = default;

  void onUpdate(std::chrono::nanoseconds) override;
  void  onRender() override;
  void  onCollision() override;

  void  PressPlayerKey(KEY key);

  Point GetPlayerPoint();
  Point GetPlayerPrePoint();

private:

  std::shared_ptr<Visual::IPlayer>playerViz_;
  Point point_;

  double vx_;
  double vy_;

  double ax_;
  double ay_;
  PLAYER_STATE_X player_state_x;
  PLAYER_STATE_Y player_state_y;
  Point pre_point_;
};
#endif // PLAYER_H
