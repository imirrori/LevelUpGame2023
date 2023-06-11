#ifndef SCORE_HPP
#define SCORE_HPP

#include "interface/IEntity.hpp"
#include "interface/IVizScore.hpp"
#include "Coin.hpp"
#include "Player.hpp"
#include <memory>

class Score
  : public IEntity {
public:

  Score(std::shared_ptr<Visual::IScore>scoreViz,
        std::shared_ptr<Player>        player,
        std::shared_ptr<Coin>          coin);

  virtual ~Score() = default;

  void onUpdate(std::chrono::nanoseconds duration) override;
  void onRender() override;
  void onCollision() override;

  int  GetCurrentScore();
  void AddScore();

private:

  std::shared_ptr<Visual::IScore>scoreViz_;
  std::shared_ptr<Player>player_;
  std::shared_ptr<Coin>coin_;
  int get_coins_;
};

#endif // SCORE_HPP
