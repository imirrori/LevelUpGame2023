#ifndef IPLAYER_HPP
#define IPLAYER_HPP

class IPlayer {
public:
  virtual void OnInit()                         = 0;
  virtual void OnUpdate(double deltaTime = 0.0) = 0;
  virtual void OnRender()                       = 0;

  virtual ~IPlayer() = default;
  //virtual void ShowPlayer(const int& x, const int& y) = 0;
};

#endif // IPLAYER_HPP
