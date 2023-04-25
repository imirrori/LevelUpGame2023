#ifndef PLAYERSTUB_HPP
#define PLAYERSTUB_HPP

#include "interface/IEntity.hpp"
#include "interface/IVizPlayer.hpp"

#include <memory>

class PlayerStub
  : public IEntity {
public:

  PlayerStub(std::shared_ptr<Visual::IPlayer>playerViz)
    : playerViz_(std::move(playerViz))
  {}

  void onUpdate() override {}

  void onRender() override    {
    playerViz_->ShowPlayer(10, 10);
  }

  void onCollision() override {}

private:

  std::shared_ptr<Visual::IPlayer>playerViz_;
};

#endif // PLAYERSTUB_HPP
