#ifndef GAME_H
#define GAME_H

#include "Entity/IEntity.hpp"
#include "Entity/EntityGround.hpp"
#include "Entity/EntityMario.hpp"
#include "Level.hpp"
#include "View.hpp"

#include <box2d/box2d.h>
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
  void SetGameEvent(IEntity &entity);
  void ClearGameEvent(IEntity &entity);

  void LoadAllShader();
  void LoadAllTexture();

  static float PIXEL_TO_MARIO;

 private:
  View view;

  unsigned int width, height;

  std::vector<std::shared_ptr<IEntity>> scene_objects;

  std::unique_ptr<EntityMario> mario;
  std::unique_ptr<EntityGround> ground;
  std::unique_ptr<Level> level;

  // physics
  b2World *MarioWorld;
  std::unique_ptr<contactListener> contact_listener;

};

#endif // GAME_H
