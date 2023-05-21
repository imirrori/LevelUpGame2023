#include "MapTypes.hpp"
#include "Score.hpp"

#include <algorithm>

Score::Score(std::shared_ptr<Visual::IScore>scoreViz,
             std::shared_ptr<Player>    player,
             std::shared_ptr<Map>           map)
  : scoreViz_(std::move(scoreViz))
  , player_(std::move(player))
  , map_(std::move(map))
  , coin_(0)
{}

void Score::onUpdate()    {
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
  auto vec = map_->GetBlocks();

  std::size_t x = player_->GetPlayerX_();
  std::size_t y = player_->GetPlayerY_();

  auto itr =
    find_if(vec.begin(), vec.end(), [vec, x, y](decltype (vec[0])& element)
  {
    if ((element.x == x) && (element.y == y))
    {
      return element.type;
    }
    else return 0;
  });

  if (itr->type == COIN)
  {
    ++coin_;
    map_->Change_Block(x, y, GROUND);
  }
}
