#include "MapTypes.hpp"
#include "Score.hpp"

#include <cmath>

Score::Score(std::shared_ptr<Visual::IScore>scoreViz,
             std::shared_ptr<Player>        player,
             std::shared_ptr<Map>           map)
  : scoreViz_(std::move(scoreViz))
  , player_(std::move(player))
  , map_(std::move(map))
  , coin_(0)
{}

void Score::onUpdate(std::chrono::nanoseconds) {
}

void Score::onRender()    {
  scoreViz_->ShowScore(coin_);
}

void Score::onCollision() {
}

int  Score::GetCurrentScore()
{
  return coin_;
}

void Score::AddScore()
{
  const std::vector<Map::Block> map_copy = map_->GetBlocks();
  const Point player_copy                = player_->GetPlayerPoint();

  for (auto itr = map_copy.begin(); itr != map_copy.end(); ++itr)
  {
    if (
      (itr->point.x == std::round(player_copy.x)) &&
      (itr->point.y == std::round(player_copy.y))
      )
    {
      if (itr->type == COIN)
      {
        ++coin_;
        map_->Change_Block(itr->point, SKY);
      }
    }
  }
}
