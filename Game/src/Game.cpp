#include "ContactListener.hpp"
#include "Game.hpp"
#include "Graphics/Render.hpp"
#include "Entity/EntityGround.hpp"
#include "Entity/EntityMario.hpp"
#include "Level.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>
#include <memory>

using namespace glm;

void Game::Run() {

}

Game::Game() {

  std::cout << "Game initialized" << std::endl;

}

void Game::OnInit() {
  LoadAllShader();
  LoadAllTexture();

  Render::onInit();

  // Physics Init
  b2Vec2 gravity(0, -20);
  this->MarioWorld = new b2World(gravity); // gravity -10
  contact_listener = std::make_unique<ContactListener>(ContactListener(*MarioWorld));

  mario = std::make_shared<Entity>(EntityMario(*MarioWorld));
  SetGameEvent(mario->GetEventHandler());

  ground = std::make_unique<Entity>(EntityGround(*MarioWorld));
  SetGameEvent(ground->GetEventHandler());

  level = std::make_unique<Entity>(Level(*MarioWorld));
  SetGameEvent(level->GetEventHandler());

}
void Game::OnUpdate(double delta) {

}
void Game::OnRender() {

}
void Game::SetGameEvent(const std::shared_ptr<Entity> &entity) {
  scene_objects.push_back(entity);
}
void Game::ClearGameEvent(const std::shared_ptr<Entity> &entity) {
  for (auto it = scene_objects.begin(); it!=scene_objects.end(); ++it) {

	if (*it==entity) {
	  scene_objects.erase(it);
	}

  }

}

Game::~Game() = default;