#ifndef IVIZPLAYER_H
#define IVIZPLAYER_H

#include "interface/Player_state.hpp"
#include "Point.h"

namespace Visual {
class IPlayer {
public:

  virtual ~IPlayer() = default;

  virtual void ShowPlayer(Point        point,
                          PLAYER_STATE state) = 0;
};
} // Visual

#endif // IVIZPLAYER_H
