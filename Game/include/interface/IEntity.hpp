//
// Created by Dmitry Morozov on 24/3/23.
//

#ifndef LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_INCLUDE_IENTITY_HPP_
#define LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_INCLUDE_IENTITY_HPP_

#include <chrono>

class IEntity {
public:

  virtual ~IEntity() = default;

  virtual void onUpdate(std::chrono::duration<uint64_t>duration) = 0;
  virtual void onRender()                                        = 0;
  virtual void onCollision()                                     = 0;
};
#endif // LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_INCLUDE_IENTITY_HPP_
