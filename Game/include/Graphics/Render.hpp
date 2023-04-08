//
// Created by Dmitry Morozov on 30/3/23.
//

#ifndef LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_GRAPHICS_RENDER_HPP_
#define LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_GRAPHICS_RENDER_HPP_
#include "GL/glew.h"

#include "View.hpp"
#include "Graphics/Shader.hpp"
#include "Texture.hpp"

class Render {
 public:
  static void onInit();
  static void onShutDown();

  static void BeginScene(View &view_cam);
  static void EndScene();

  static void DrawQuad(glm::vec2 position, float rotation, glm::vec2 scale, glm::vec4 color);
  static void DrawTexture(glm::vec2 position, float rotation, glm::vec2 scale, Texture &texture);

};

#endif //LEVELUPGAME2023_FEATURE_LEVEL_AND_ENTITY_GAME_SRC_GRAPHICS_RENDER_HPP_
