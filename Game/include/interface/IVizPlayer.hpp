#ifndef IVIZPLAYER_H
#define IVIZPLAYER_H

namespace Visual {
class IPlayer {
public:

  virtual ~IPlayer() = default;

  virtual void ShowPlayer(double x,
                          double y) = 0;
};
} // Visual

#endif // IVIZPLAYER_H
