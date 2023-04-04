#include "ContactListener.hpp"
#include "Game.hpp"
#include "Graphics/Render.hpp"
#include "Entity/EntityGround.hpp"
#include "Entity/EntityMario.hpp"
#include "EventSystem.hpp"
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

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  main_window = glfwCreateWindow(width, height, "Super Mario", nullptr, nullptr);

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

	onUpdate(delta); //FIXME:  Fail
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

  event_handler = std::make_unique<EventSystem>(EventSystem());

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
	entity->onUpdate(delta); //Fixme: Fail
  }

  view_cam.SetPosition({mario->GetPosition().x - (width/2), view_cam.GetPosition().y});
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

  Shader::LoadShader("sprite", "Resources/Shader/Sprite.vert.glsl", "Resources/Shader/Sprite.frag.glsl");
  Shader::LoadShader("flat", "Resources/Shader/FlatColor.vert.glsl", "Resources/Shader/FlatColor.frag.glsl");

}
void Game::LoadAllTexture() {

  // Mario
  Texture::LoadTexture("mario-idle", "Resources/Texture/Mario/mario-idle.png", true);
  Texture::LoadTexture("mario-run-0", "Resources/Texture/Mario/mario-run0.png", true);
  Texture::LoadTexture("mario-run-1", "Resources/Texture/Mario/mario-run1.png", true);
  Texture::LoadTexture("mario-run-2", "Resources/Texture/Mario/mario-run2.png", true);
  Texture::LoadTexture("mario-jump", "Resources/Texture/Mario/mario-jump.png", true);

  // Ground
  Texture::LoadTexture("ground", "Resources/Texture/ground.png", true);

  // Bad Mushroom
  Texture::LoadTexture("mushroom-run-0", "Resources/Texture/Mushroom/mushroom-run0.png", true);
  Texture::LoadTexture("mushroom-run-1", "Resources/Texture/Mushroom/mushroom-run1.png", true);
  Texture::LoadTexture("mushroom-dead", "Resources/Texture/Mushroom/mushroom-dead.png", true);

  // Brick
  Texture::LoadTexture("brick-0", "Resources/Texture/Brick/brick-0.png", true);
  Texture::LoadTexture("brick-1", "Resources/Texture/Brick/brick-1.png", true);
  Texture::LoadTexture("brick-2", "Resources/Texture/Brick/brick-2.png", true);

  // Coin Brick
  Texture::LoadTexture("coin-brick-idle", "Resources/Texture/CoinBrick/coin-brick.png", true);
  Texture::LoadTexture("coin-brick-break", "Resources/Texture/CoinBrick/coin-break-brick.png", true);

  // Coin
  Texture::LoadTexture("coin-0", "Resources/Texture/Coin/coin-0.png", true);
  Texture::LoadTexture("coin-1", "Resources/Texture/Coin/coin-1.png", true);
  Texture::LoadTexture("coin-2", "Resources/Texture/Coin/coin-2.png", true);
  Texture::LoadTexture("coin-3", "Resources/Texture/Coin/coin-3.png", true);
  Texture::LoadTexture("coin-4", "Resources/Texture/Coin/coin-4.png", true);
  Texture::LoadTexture("coin-5", "Resources/Texture/Coin/coin-5.png", true);

  // Pipe
  Texture::LoadTexture("pipe", "Resources/Texture/pipe.png", true);

  // Stair Brick
  Texture::LoadTexture("stair_brick", "Resources/Texture/StairBrick.png", true);

}

Game::~Game() {
  Render::onShutDown();

  delete contact_listener;
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
