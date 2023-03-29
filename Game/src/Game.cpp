#include "Game.hpp"

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
using namespace glm;

#include <common/shader.hpp>

void Game::Run() {

}

Game::Game() {

  if (not TestInitialize()) {
	std::cerr << "Failed to initialize Game" << std::endl;

	throw std::runtime_error("Failed to initialize Game");
  }

  std::cout << "Game initialized" << std::endl;

}

void Game::OnInit() {

}
void Game::OnUpdate(double delta) {

}
void Game::OnRender() {

}

Game::~Game() = default;