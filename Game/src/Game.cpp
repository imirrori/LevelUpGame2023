#include "ContactListener.hpp"
#include "Game.hpp"
#include "Graphics/Render.hpp"
#include "Entity/EntityGround.hpp"
#include "Entity/EntityMario.hpp"
#include "Input.hpp"
#include "Level.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <memory>

using namespace glm;

Game::Game(unsigned int width_, unsigned int height_) :
	width(width_), height(height_), view_cam(0, static_cast <float>(width_), 0, static_cast<float>(height_)) {

  std::cout << "Game initialized" << std::endl;

}

bool Game::Run() {

  GLFWwindow *main_window;

  if (!glfwInit())
	return false;

  main_window = glfwCreateWindow(static_cast<int>(width), static_cast<int>(height), "Super Mario", nullptr, nullptr);

  if (!main_window) {
	glfwTerminate();

	return false;
  }

  glfwSetKeyCallback(main_window, key_callback_);
  glfwSetFramebufferSizeCallback(main_window, framebuffer_size_callback_);
  glfwMakeContextCurrent(main_window);

  GLenum err = glewInit();

  if (GLEW_OK!=err) {
	std::cerr << "GLEW Init Error!";
	return false;
  }

  onInit();

  float currentTime = 0.f;
  float lastTime = 0.f;
  float delta;

  while (!glfwWindowShouldClose(main_window)) {

	currentTime = static_cast<float>(glfwGetTime());

	delta = currentTime - lastTime;
	lastTime = currentTime;

	glClearColor(0.363f, 0.914f, 0.937f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	onUpdate(delta);
	onRender();

	glfwSwapBuffers(main_window);
	glfwPollEvents();
  }

  glfwTerminate();

  return true;
}

void Game::onInit() {
  LoadAllShader();
  LoadAllTexture();

  Render::onInit();

  // Physics initialization
  b2Vec2 gravity(0, -20);

  this->MarioWorld = new b2World(gravity);

  if (not MarioWorld) {
	throw std::runtime_error("Failed to create b2World");
  }

  contact_listener = std::make_unique<ContactListener>(ContactListener(*MarioWorld));

  mario = std::make_shared<Entity>(EntityMario(*MarioWorld));
  SetGameEvent(mario->GetEventHandlers()); //TODO: Refactoring to Event class

  ground = std::make_unique<Entity>(EntityGround(*MarioWorld));
  SetGameEvent(ground->GetEventHandlers());

  level = std::make_unique<Entity>(Level(*MarioWorld));

  if (MarioWorld) {
	SetGameEvent(level->GetEventHandlers());
  } else {
	throw std::runtime_error("Error loading world");
  }

}

void Game::onUpdate(float delta) {

  for (const auto &entity : scene_objects) {
	entity->onUpdate(delta);
  }

  view_cam.SetPosition({mario->GetPosition().x - (static_cast<float>(width)/2), view_cam.GetPosition().y});
  MarioWorld->Step(delta, 8, 3);

}

void Game::onRender() {
  Render::BeginScene(view_cam);

  for (auto object : scene_objects) {
	object->onRender();
  }

  Render::EndScene();
}

void Game::ClearGameEvent(std::shared_ptr<Entity> &entity) {

  for (auto it = scene_objects.begin(); it!=scene_objects.end(); ++it) {

	if (*it==entity) {
	  scene_objects.erase(it);
	}

  }

}

void Game::LoadAllShader() {

  Shader::LoadShader("sprite", "Game/Resources/Shader/Sprite.vert.glsl", "Game/Resources/Shader/Sprite.frag.glsl");
  Shader::LoadShader("flat", "Game/Resources/Shader/FlatColor.vert.glsl", "Game/Resources/Shader/FlatColor.frag.glsl");

}
void Game::LoadAllTexture() {

  // Mario
  Texture::LoadTexture("mario-idle", "Game/Resources/Texture/Mario/mario-idle.png", true);
  Texture::LoadTexture("mario-run-0", "Game/Resources/Texture/Mario/mario-run0.png", true);
  Texture::LoadTexture("mario-run-1", "Game/Resources/Texture/Mario/mario-run1.png", true);
  Texture::LoadTexture("mario-run-2", "Game/Resources/Texture/Mario/mario-run2.png", true);
  Texture::LoadTexture("mario-jump", "Game/Resources/Texture/Mario/mario-jump.png", true);

  // Ground
  Texture::LoadTexture("ground", "Game/Resources/Texture/ground.png", true);

  // Bad Mushroom
  Texture::LoadTexture("mushroom-run-0", "Game/Resources/Texture/Mushroom/mushroom-run0.png", true);
  Texture::LoadTexture("mushroom-run-1", "Game/Resources/Texture/Mushroom/mushroom-run1.png", true);
  Texture::LoadTexture("mushroom-dead", "Game/Resources/Texture/Mushroom/mushroom-dead.png", true);

  // Brick
  Texture::LoadTexture("brick-0", "Game/Resources/Texture/Brick/brick-0.png", true);
  Texture::LoadTexture("brick-1", "Game/Resources/Texture/Brick/brick-1.png", true);
  Texture::LoadTexture("brick-2", "Game/Resources/Texture/Brick/brick-2.png", true);

  // Coin Brick
  Texture::LoadTexture("coin-brick-idle", "Game/Resources/Texture/CoinBrick/coin-brick.png", true);
  Texture::LoadTexture("coin-brick-break", "Game/Resources/Texture/CoinBrick/coin-break-brick.png", true);

  // Coin
  Texture::LoadTexture("coin-0", "Game/Resources/Texture/Coin/coin-0.png", true);
  Texture::LoadTexture("coin-1", "Game/Resources/Texture/Coin/coin-1.png", true);
  Texture::LoadTexture("coin-2", "Game/Resources/Texture/Coin/coin-2.png", true);
  Texture::LoadTexture("coin-3", "Game/Resources/Texture/Coin/coin-3.png", true);
  Texture::LoadTexture("coin-4", "Game/Resources/Texture/Coin/coin-4.png", true);
  Texture::LoadTexture("coin-5", "Game/Resources/Texture/Coin/coin-5.png", true);

  // Pipe
  Texture::LoadTexture("pipe", "Game/Resources/Texture/pipe.png", true);

  // Stair Brick
  Texture::LoadTexture("stair_brick", "Game/Resources/Texture/StairBrick.png", true);

}

Game::~Game() {
  Render::onShutDown();

  contact_listener.reset();
  level.reset();

  delete MarioWorld; //TODO:  Refactor to smart pointer

}
void Game::key_callback_(GLFWwindow *window, int key, int scancode, int action, int mods) {

  if (key==GLFW_KEY_ESCAPE && action==GLFW_PRESS)
	glfwSetWindowShouldClose(window, true);

  if (key >= 0 && key < 1024 && action==GLFW_PRESS) {
	Input::keys[key] = true;
  }

  if (key >= 0 && key < 1024 && action==GLFW_RELEASE) {
	Input::keys[key] = false;
	Input::keyUp[key] = false;
  }

}
void Game::framebuffer_size_callback_(GLFWwindow *window, int width, int height) {

  glViewport(0, 0, width, height);

}
void Game::SetGameEvent(std::vector<std::shared_ptr<Entity>> entities) {

  for (const auto &entity : entities) {

	scene_objects.push_back(entity);

  }

}
