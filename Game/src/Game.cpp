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

Game::~Game() = default;