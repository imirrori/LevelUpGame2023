#ifndef IVIZPLAYER_H
#define IVIZPLAYER_H

namespace Visual {
class IPlayer {
public:
  virtual void ShowPlayer(const int& x, const int& y) = 0;

  virtual void OnInit()                               = 0;
  virtual void OnUpdate(double deltaTime = 0.0)       = 0;
  virtual void OnRender()                             = 0;

  virtual ~IPlayer()                                  = default;
};
} // Visual

#endif // IVIZPLAYER_H
