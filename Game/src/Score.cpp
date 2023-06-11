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

void Score::onUpdate(std::chrono::nanoseconds) {}

void Score::onRender()    {
  scoreViz_->ShowScore(coin_);
}

void Score::onCollision() {}

int  Score::GetCurrentScore()
{
  return coin_;
}

void Score::AddScore()
{
  const Point  player_point = player_->GetPlayerPoint();
  const double z            = 0.2;

  const int x_1 = static_cast<int>(player_point.x);
  const int x_2 = x_1 + 1;

  const int y_1 = static_cast<int>(player_point.y);
  const int y_2 = y_1 + 1;

  auto checnge = [this](const std::vector<Point>& points) {
                   for (auto point: points) {
                     if (map_->GetBlock(point) == MAP_TYPES::COIN) {
                       map_->Change_Block(point, MAP_TYPES::SKY);
                       ++coin_;
                     }
                   }
                 };

  std::vector<Point> points;

  points.push_back(Point{ static_cast<double>(x_1), static_cast<double>(y_1) });

  if (player_point.x - x_1 > z) {
    points.push_back(Point{ static_cast<double>(x_2),
                            static_cast<double>(y_1) });
  }

  if (player_point.y - y_1 > z) {
    points.push_back(Point{ static_cast<double>(x_1),
                            static_cast<double>(y_2) });
  }

  if ((player_point.x - x_1 > z) && (player_point.y - y_1 > z)) {
    points.push_back(Point{ static_cast<double>(x_2),
                            static_cast<double>(y_2) });
  }

  checnge(points);
}
