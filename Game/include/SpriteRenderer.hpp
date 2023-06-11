#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include "Texture.hpp"
#include "Shader.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class SpriteRenderer
{
public:
  SpriteRenderer(Shader &shader);
  ~SpriteRenderer();
  void DrawSprite(Textures::Texture &texture, glm::vec2 position, glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));

private:
  Shader       _shader;
  unsigned int _quadVAO;

  void initRenderData();
};

#endif // SPRITERENDERER_H
