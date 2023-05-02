//
// Created by Dmitry Morozov on 24/3/23.
//

#ifndef LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_INCLUDE_MAP_HPP_
#define LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_INCLUDE_MAP_HPP_

#include "interface/IEntity.hpp"
#include "interface/IVizMap.hpp"

#include <string>
#include <vector>
#include <memory>

class Map
  : public IEntity {
public:

  explicit Map(std::shared_ptr<Visual::IMap>mapViz);
  Map(const std::string          & file_name,
      std::shared_ptr<Visual::IMap>mapViz);
  ~Map() = default;

  [[nodiscard]] std::size_t width() const {
    return width_;
  };

  [[nodiscard]] std::size_t height() const {
    return height_;
  };

  void onUpdate() override;
  void onRender() override;
  void onCollision() override;

private:

  struct Block
  {
    size_t x;
    size_t y;
    int    type;
  };

  std::size_t width_;
  std::size_t height_;

  std::string map_;
  std::vector<Block>blocks_;

  std::shared_ptr<Visual::IMap>mapViz_;

  void InitBlocks();

  // Debug purposes only
  const std::string default_map_ =
    "##########m#############################################################################################################################################################################################"
    "##########p##########c#############################################################################################c#######################bbcbc########################################################"
    "##########s######################################################################bbbbbbbbbb####bbbc################################bbb#################################################################s"
    "##########b#################################################################m#########################################################################################################################ss"
    "##########c###c####bcbcb##################################################bbcbb########################bb#######c##c##c#######b##############bb########s##s##########ss##s#########bbcb##############sss"
    "##########m#######################################################################################b###################################################ss##ss########sss##ss#########################ssss"
    "##########p##########################################################################################################################################sss##sss######ssss##sss#######################sssss"
    "######################m#######p####m####p######m#####p#####m###p########m######################m###########################################m########ssss##ssss####sssss##ssss###p####m#####p######ssssss";
};

#endif // LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_INCLUDE_MAP_HPP_
