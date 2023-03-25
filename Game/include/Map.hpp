//
// Created by Dmitry Morozov on 24/3/23.
//

#ifndef LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_INCLUDE_MAP_HPP_
#define LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_INCLUDE_MAP_HPP_

#include <string>
#include <vector>

class Map {
 public:
  Map();
  explicit Map(const std::string &file_name);
  ~Map() = default;
  [[nodiscard]] std::size_t width() const { return width_; };
  [[nodiscard]] std::size_t height() const { return height_; };
  [[nodiscard]] const std::string &GetMap() const { return map_; };

 private:
  std::size_t width_;
  std::size_t height_;

  std::string map_;

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

};

#endif //LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_INCLUDE_MAP_HPP_
