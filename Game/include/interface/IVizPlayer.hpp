#ifndef IVIZPLAYER_H
#define IVIZPLAYER_H

#include "Point.h"

namespace Visual {
class IPlayer {
public:

  virtual ~IPlayer() = default;

  virtual void ShowPlayer(Point point) = 0;
};
} // Visual

#endif // IVIZPLAYER_H
