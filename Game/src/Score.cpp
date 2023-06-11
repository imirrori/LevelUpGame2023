#include "Score.hpp"

#include <cmath>

Score::Score(std::shared_ptr<Visual::IScore>scoreViz,
             std::shared_ptr<Player>        player,
             std::shared_ptr<Coin>          coin)
  : scoreViz_(std::move(scoreViz))
  , player_(std::move(player))
  , coin_(std::move(coin))
  , get_coins_(0)
{}

void Score::onUpdate(std::chrono::nanoseconds) {
}

void Score::onRender()    {
  scoreViz_->ShowScore(get_coins_);
}

void Score::onCollision() {
}

int  Score::GetCurrentScore()
{
  return get_coins_;
}

void Score::AddScore()
{
  const Point player_copy       = player_->GetPlayerPoint();
  std::vector<Point> coins_copy = coin_->GetCoins();

  for (auto el: coins_copy)
  {
    if ((std::round(player_copy.x) == el.x) &&
        (std::round(player_copy.y) == el.y))
    {
      ++get_coins_;
      coin_->DeleteCoin(el);
    }
  }
}
