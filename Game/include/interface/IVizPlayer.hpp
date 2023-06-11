#ifndef IVIZPLAYER_H
#define IVIZPLAYER_H

#include "interface/Player_state.hpp"
#include "Point.h"

namespace Visual {
class IPlayer {
public:

  virtual ~IPlayer() = default;

  virtual void ShowPlayer(Point          point,
                          PLAYER_STATE_X state_x,
                          PLAYER_STATE_Y state_y) = 0;
  virtual void ShowCoin(Point coin)               = 0;
};
} // Visual

#endif // IVIZPLAYER_H
