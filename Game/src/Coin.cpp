#include "Coin.hpp"
#include <limits>
#include <algorithm>

Coin::Coin(std::shared_ptr<Visual::IPlayer>coinViz)
  : coinViz_(std::move(coinViz))
  , coins_{{ 0, 1 }, { 2, 2 }, { 5, 1 }, { 10, 3 }, { 17, 4 }, { 25, 2 }}
{}

void Coin::onUpdate(std::chrono::nanoseconds duration)
{
}

void Coin::onRender()
{
  for (const auto& coin: coins_)
  {
    coinViz_->ShowCoin(coin);
  }
}

void              Coin::onCollision() {
}

std::vector<Point>Coin::GetCoins()
{
  return coins_;
}

void Coin::DeleteCoin(Point point)
{
  auto itr = std::find_if(coins_.begin(), coins_.end(), [point](auto& el){
    if ((point.x == el.x) && (point.y == el.y)) return true;
    else false;
  });

  if (itr != coins_.end())
  {
    coins_.erase(itr);
  }
}
