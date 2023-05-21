#ifndef SCORE_HPP
#define SCORE_HPP

#include "interface/IEntity.hpp"
#include "interface/IVizScore.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include <memory>

class Score
  : public IEntity {
public:

  Score(std::shared_ptr<Visual::IScore>scoreViz,
        std::shared_ptr<Player>        player,
        std::shared_ptr<Map>           map);

  virtual ~Score() = default;

  void onUpdate(std::chrono::duration<uint64_t>duration) override;
  void onRender() override;
  void onCollision() override;

  int  GetCurrentScore();
  void AddScore();

private:

  std::shared_ptr<Visual::IScore>scoreViz_;
  std::shared_ptr<Player>player_;
  std::shared_ptr<Map>map_;
  int coin_;
};

#endif // SCORE_HPP
