#include "MapTypes.hpp"
#include "Score.hpp"

#include <algorithm>

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
  auto point     = player_->GetPlayerPoint();
  auto pre_point = player_->GetPlayerPrePoint();
  auto map       = map_->GetBlocks();

  if (point.y == (map[point.y].type == GROUND))
  {
    point.y = point.y + 1;
    player_->ChangePlayerPoint(point);
  }

  if (point.y == (map[point.y + 1].type == GROUND))
  {
    point.y = map[point.y - 1].point.y;
    player_->ChangePlayerPoint(point);
  }

  if (point.x == (map[point.x].type == GROUND))
  {
    point.x = pre_point.x;
    player_->ChangePlayerPoint(point);
  }
}

int Score::GetCurrentScore()
{
  return coin_;
}

void Score::AddScore()
{
  // auto vec = map_->GetBlocks();

  // std::size_t x = player_->GetPlayerX_();
  // std::size_t y = player_->GetPlayerY_();

  // auto itr =
  //  find_if(vec.begin(), vec.end(), [vec, x, y](decltype (vec[0])& element)
  // {
  //  if ((element.x == x) && (element.y == y))
  //  {
  //    return element.type;
  //  }
  //  else return 0;
  // });

  // if (itr->type == COIN)
  // {
  //  ++coin_;
  //  map_->Change_Block(x, y, GROUND);
  // }
}
