//
// Created by Dmitry Morozov on 24/3/23.
//

#include "Map.hpp"

#include <fstream>

Map::Map(const std::string &file_name) {

  std::ifstream file(file_name);

  if (!file.is_open()) {
	throw std::runtime_error("File not found");
  }

  std::string line;

  std::size_t tmp_width = 0;
  std::size_t tmp_height = 0;
  std::size_t line_before_width = tmp_width;

  while (std::getline(file, line)) {

	tmp_width = line.length();

	if (tmp_width!=line_before_width && tmp_height!=0) {
	  throw std::runtime_error("Map is not rectangular");
	}

	line_before_width = tmp_width;
	tmp_height++;
	map_ += line;
  }

  width_ = tmp_width;
  height_ = tmp_height;

}
Map::Map() {

  map_ = default_map_;
  width_ = 200;
  height_ = 9;

}

void Map::PrintMap(const std::string &map) {

}
