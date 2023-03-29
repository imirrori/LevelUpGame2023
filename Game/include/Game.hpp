#ifndef GAME_H
#define GAME_H

#include "View.hpp"
#include "IEntity.hpp"
#include <vector>
#include <Box2D/Box2D.h>

class Game {
 public:
  Game();
  ~Game();

  void Run();

  void OnInit();
  void OnUpdate(double delta);
  void OnRender();

 private:
  bool TestInitialize();
 public:
  void RegisterGameEvent(IEntity &entity);
  void UnRegisterGameEvent(IEntity &entity);

  void LoadAllShader();
  void LoadAllTexture();

  static float PIXEL_TO_M;

 private:
  View view;

  unsigned int width, height;
  std::vector<std::shared_ptr<IEntity>> scene_objects;

  Mario *mario;
  Ground *ground;
  Level *level;

  // physics
  b2World *physicsWorld;
  ContactListener *contactListener;

};

};

#endif // GAME_H
