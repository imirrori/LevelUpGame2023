#ifndef IPLAYER_HPP
#define IPLAYER_HPP

class IPlayer {
public:

  virtual ~IPlayer() = default;

  virtual void ShowPlayer(int x,
                          int y) const = 0;
};

// проверка для коммита
#endif // IPLAYER_HPP
