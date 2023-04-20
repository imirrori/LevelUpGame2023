#ifndef IPLAYERVISUALIZER_H
#define IPLAYERVISUALIZER_H

class IPlayerVisualizer
{
public:
  virtual void ShowPlayer(const int& x, const int& y) = 0;
  virtual ~IPlayerVisualizer() = default;

private:
};

#endif // IPLAYERVISUALIZER_H
