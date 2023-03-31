#include "Game.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>

using namespace glm;

void Game::Run() {

}

Game::Game() {

  std::cout << "Game initialized" << std::endl;

}

void Game::OnInit() {

}
void Game::OnUpdate(double delta) {

}
void Game::OnRender() {

}
void Game::SetGameEvent(std::shared_ptr<IEntity> &entity) {
  scene_objects.push_back(entity);
}
void Game::ClearGameEvent(std::shared_ptr<IEntity> &entity) {
  for (auto it = scene_objects.begin(); it!=scene_objects.end(); ++it) {

	if (*it==entity) {
	  scene_objects.erase(it);
	}

  }

}

Game::~Game() = default;