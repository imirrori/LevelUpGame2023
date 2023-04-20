//
// Created by Dmitry Morozov on 21/4/23.
//

#ifndef MARIO_GAME_SRC_MAPPARSER_HPP_
#define MARIO_GAME_SRC_MAPPARSER_HPP_

#include "interface/IEntity.hpp"

#include <vector>

class MapParser {

 public:

  MapParser() = default;

  explicit MapParser(const std::string &map_string);

  static std::vector<IEntity *> Parse(const std::string &map_string);

  std::vector<IEntity *> Parse();

 private:

  std::string map_string_;
  std::vector<IEntity *> entities;

};

#endif //MARIO_GAME_SRC_MAPPARSER_HPP_
