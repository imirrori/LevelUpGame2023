#ifndef PLAYERSTUB_HPP
#define PLAYERSTUB_HPP

#include "IEntity.hpp"
#include "IPlayer.hpp"

#include <memory>

class PlayerStub
  : public IEntity {
public:

  PlayerStub(std::shared_ptr<IPlayer>playerViz)
    : playerViz_(std::move(playerViz))
  {}

  void onUpdate() override {}

  void onRender() override    {
    playerViz_->ShowPlayer(10, 10);
  }

  void onCollision() override {}

private:

  std::shared_ptr<IPlayer>playerViz_;
};

#endif // PLAYERSTUB_HPP
