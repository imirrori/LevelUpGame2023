#ifndef PLAYER_H
#define PLAYER_H

#include "interface/IEntity.hpp"
#include "interface/IVizPlayer.hpp"
#include "interface/ISettings.hpp"
#include "Map.hpp"

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

private:

  std::shared_ptr<Settings::ISettings> settings;
  const int block_pixel = std::get<int>(settings->GetValue("visual", "block_size"));
  const int player_pixel = std::get<int>(settings->GetValue("visual", "player_size"));

  std::shared_ptr<Visual::IPlayer>playerViz_;
  std::shared_ptr<Map> map;
  Point point_;

  double vx_;
  double vy_;

  double ax_;
  double ay_;
  PLAYER_STATE_X player_state_x;
  PLAYER_STATE_Y player_state_y;
};
#endif // PLAYER_H
