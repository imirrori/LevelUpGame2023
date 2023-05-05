//
// Created by Dmitry Morozov on 24/3/23.
//

#include "Map.hpp"

#include <fstream>

Map::Map(const std::string& file_name, std::shared_ptr<Visual::IMap>mapViz_)
  : mapViz_(std::move(mapViz_))
{
  std::ifstream file(file_name);

  if (!file.is_open()) {
    throw std::runtime_error("File not found");
  }

  std::string line;

  std::size_t tmp_width         = 0;
  std::size_t tmp_height        = 0;
  std::size_t line_before_width = tmp_width;

  while (std::getline(file, line)) {
    tmp_width = line.length();

    if ((tmp_width != line_before_width) && (tmp_height != 0)) {
      throw std::runtime_error("Map is not rectangular");
    }

    line_before_width = tmp_width;
    tmp_height++;
    map_ += line;
  }

  width_  = tmp_width;
  height_ = tmp_height;
  InitBlocks();
}

Map::Map(std::shared_ptr<Visual::IMap>mapViz_)
  : mapViz_(std::move(mapViz_))
{
  map_    = default_map_;
  width_  = 200;
  height_ = 8;
  InitBlocks();
}

void Map::onUpdate()
{}

void Map::onRender()
{
  for (const auto& block: blocks_)
  {
    mapViz_->PrintBlock(block.x, block.y, block.type);
  }
}

void Map::onCollision()
{}


void Map::InitBlocks()
{
  for (std::size_t y = 0; y < height(); ++y)
  {
    for (std::size_t x = 0; x < width(); ++x)
    {
      switch (map_[y * width() + x]) {
        case 'b':
          blocks_.push_back(Block{ x, height() - y - 1, 0 });
          break;

        case 'c':
          blocks_.push_back(Block{ x, height() - y - 1, 1 });
          break;

        case 'p':
          blocks_.push_back(Block{ x, height() - y - 1, 2 });
          break;

        case 'm':
          blocks_.push_back(Block{ x, height() - y - 1, 3 });
          break;

        case 's':
          blocks_.push_back(Block{ x, height() - y - 1, 4 });
          break;

        case '#':
          blocks_.push_back(Block{ x, height() - y - 1, 5 });
          break;

        default: break;
      }
    }
  }
}
