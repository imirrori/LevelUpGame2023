#ifndef GAME_H
#define GAME_H

#include "IEntity.hpp"
#include "View.hpp"

#include <Box2D/Box2D.h>
#include <vector>

class Game {
 public:
  Game();
  ~Game();

  void Run();

  void OnInit();
  void OnUpdate(double delta);
  void OnRender();


 public:
  void RegisterGameEvent(IEntity &entity);
  void ClearGameEvent(IEntity &entity);

  void LoadAllShader();
  void LoadAllTexture();

  static float PIXEL_TO_MARIO;

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
