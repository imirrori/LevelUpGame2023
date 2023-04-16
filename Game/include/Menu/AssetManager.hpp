//
// Created by Dmitry Morozov on 16/4/23.
//

#ifndef MARIO_GAME_SRC_MENU_ASSETMANAGER_HPP_
#define MARIO_GAME_SRC_MENU_ASSETMANAGER_HPP_

#include<map>
#include <SFML/Graphics.hpp>

class AssetManager {
 public:

  AssetManager();

  static sf::Texture &GetTexture(std::string const &filename);

 private:

  std::map<std::string, sf::Texture> m_Textures;

  static AssetManager *sInstance;
};

#endif //MARIO_GAME_SRC_MENU_ASSETMANAGER_HPP_
