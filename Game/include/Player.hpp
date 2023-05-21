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

  void onUpdate(std::chrono::duration<uint64_t>) override;
  void onRender() override;
  void onCollision() override;

  void PressPlayerKey(KEY key);

  int  GetPlayerX_();
  int  GetPlayerY_();

private:

  std::shared_ptr<Visual::IPlayer>playerViz_;
  int x_;
  int y_;

  int vx_;
  int vy_;

  int ax_;
  int ay_;
};
#endif // PLAYER_H
