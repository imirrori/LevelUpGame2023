#ifndef GAME_H
#define GAME_H

#include "GL/glew.h"

#include "Input.hpp"
#include "Entity/IEntity.hpp"
#include "Entity/EntityGround.hpp"
#include "Entity/EntityMario.hpp"
#include "Level.hpp"
#include "View.hpp"
#include "ContactListener.hpp"

#include <GLFW/glfw3.h>
#include "box2d/box2d.h"
#include <vector>

class Game {
 public:
  Game(unsigned int width, unsigned int height);
  ~Game();

  bool Run();

  void onInit();
  void onUpdate(float delta);
  void onRender();

 public:
  void SetGameEvent(std::vector<std::shared_ptr<Entity>> entities);

  void ClearGameEvent(std::shared_ptr<Entity> &entity);

  static void LoadAllShader();
  static void LoadAllTexture();

  static constexpr float PIXEL_TO_M = 150.f;

 private:
  View view_cam;

  unsigned int width, height;

  std::vector<std::shared_ptr<IEntity>> scene_objects;

  std::shared_ptr<Entity> mario;
  std::unique_ptr<Entity> ground;
  std::unique_ptr<Entity> level;

  b2World *MarioWorld{};
  std::unique_ptr<ContactListener> contact_listener;

  static void key_callback_(GLFWwindow *window, int key, int scancode, int action, int mods);
  static void framebuffer_size_callback_(GLFWwindow *window, int width, int height);

};

#endif // GAME_H
