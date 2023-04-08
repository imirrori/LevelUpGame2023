#ifndef GAME_H
#define GAME_H

#include "box2d/box2d.h"
#include "GL/glew.h"

#include "ContactListener.hpp"
#include "Entity/EntityGround.hpp"
#include "Entity/EntityMario.hpp"
#include "EventSystem.hpp"
#include "Input.hpp"
#include "interface/IEntity.hpp"
#include "interface/IEventHandler.hpp"
#include "Level.hpp"
#include "View.hpp"

#include <GLFW/glfw3.h>
#include <memory>
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

  static void LoadAllShader();
  static void LoadAllTexture();

  static constexpr float PIXEL_TO_M = 150.f;

 private:
  View view_cam;

  unsigned int width, height;

  EventSystem event_handler;

  EntityMario *mario;
  EntityGround *ground;
  Level *level;

  b2World *MarioWorld = nullptr;

  ContactListener *contact_listener;

  static void key_callback_(GLFWwindow *window, int key, int scancode, int action, int mods);
  static void framebuffer_size_callback_(GLFWwindow *window, int width, int height);

};

#endif // GAME_H
