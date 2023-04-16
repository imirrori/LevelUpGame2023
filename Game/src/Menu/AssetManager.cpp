//
// Created by Dmitry Morozov on 16/4/23.
//

#include "Menu/AssetManager.hpp"

#include <cassert>

AssetManager *AssetManager::sInstance = nullptr;

AssetManager::AssetManager() {

  assert(sInstance==nullptr);
  sInstance = this;

}

sf::Texture &AssetManager::GetTexture(std::string const &filename) {

  auto &texMap = sInstance->m_Textures;

  auto pairFound = texMap.find(filename);

  if (pairFound!=texMap.end()) {

	return pairFound->second;

  } else {

	auto &texture = texMap[filename];

	texture.loadFromFile(filename);

	return texture;
  }

}
