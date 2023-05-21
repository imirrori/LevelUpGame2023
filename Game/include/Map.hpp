//
// Created by Dmitry Morozov on 24/3/23.
//

#ifndef LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_INCLUDE_MAP_HPP_
#define LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_INCLUDE_MAP_HPP_

#include "interface/IEntity.hpp"
#include "interface/IVizMap.hpp"
#include "MapTypes.hpp"

#include <string>
#include <vector>
#include <memory>

class Map : public IEntity {
public:

  explicit Map(std::shared_ptr<Visual::IMap>mapViz);

  Map(const std::string          & file_name,
      std::shared_ptr<Visual::IMap>mapViz);

  ~Map() override = default;

  [[nodiscard]] std::size_t width() const {
    return width_;
  };

  [[nodiscard]] std::size_t height() const {
    return height_;
  };

  void                             onUpdate(
    std::chrono::duration<uint64_t>duration) override;
  void                             onRender() override;
  void                             onCollision() override;

  [[nodiscard]] const std::string& GetMap() const {
    return map_;
  };

private:

  struct Block {
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
    "########################################################################################################################################################################################################"
    "#####################c#############################################################################################c#######################bbcbc########################################################"
    "#################################################################################bbbbbbbbbb####bbbc################################bbb#################################################################s"
    "############################################################################m#########################################################################################################################ss"
    "##############c####bcbcb##################################################bbcbb########################bb#######c##c##c#######b##############bb########s##s##########ss##s#########bbcb##############sss"
    "##################################################################################################b###################################################ss##ss########sss##ss#########################ssss"
    "#####################################################################################################################################################sss##sss######ssss##sss#######################sssss"
    "######################m#######p####m####p######m#####p#####m###p########m######################m###########################################m########ssss##ssss####sssss##ssss###p####m#####p######ssssss";

public:

  // for class score:
  std::vector<Block>GetBlocks();
  void              Change_Block(size_t    x,
                                 size_t    y,
                                 MAP_TYPES type);
};

#endif // LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_INCLUDE_MAP_HPP_
