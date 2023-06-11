#ifndef COIN_HPP
#define COIN_HPP

#include "interface/IEntity.hpp"
#include "interface/IVizPlayer.hpp"

#include <memory>
#include <vector>

class Coin
  : public IEntity {
public:

  Coin(std::shared_ptr<Visual::IPlayer>coinViz);
  ~Coin() override = default;

  void onUpdate(std::chrono::nanoseconds) override;
  void              onRender() override;
  void              onCollision() override;

  std::vector<Point>GetCoins();
  void              DeleteCoin(Point point);

private:

  std::shared_ptr<Visual::IPlayer>coinViz_;
  std::vector<Point>coins_;
};

#endif // COIN_HPP
