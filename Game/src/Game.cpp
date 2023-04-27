#include "ContactListener.hpp"
#include "Entity/EntityGround.hpp"
#include "Entity/EntityMario.hpp"
#include "Game.hpp"
#include "GAME_STATES.hpp"
#include "Graphics/Render.hpp"
#include "Input.hpp"
#include "Level.hpp"
#include "Menu/MainMenu.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <memory>

using namespace glm;
using STATE = State::GAME_STATES;

namespace Game {

Game::Game(unsigned int width_, unsigned int height_)
	:
	width(width_), height(height_), view_cam(0, static_cast <float>(width_), 0, static_cast<float>(height_)) {

//  main_menu = std::make_unique<MainMenu>();

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

	if (GLEW_OK != err) {
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

	Graphics::Render::onInit();

	// Physics initialization
	b2Vec2 gravity(0, -20);

	this->MarioWorld = new b2World(gravity);

	if (not MarioWorld) {
		throw std::runtime_error("Failed to create b2World");
	}

	contact_listener = new ContactListener(*MarioWorld);

	mario = new EntityMario(event_handler, *MarioWorld);

	level = new Level(event_handler, *MarioWorld);

	ground = new EntityGround(event_handler, *MarioWorld, level->getLevelWidth());

	if (MarioWorld) {
		std::cout << "Mario World Created" << std::endl;
	} else {
		throw std::runtime_error("Error loading world");
	}

}

void Game::onUpdate(float delta) {

	auto ev_list = event_handler.getEventsList();

	auto cur_gs_ = game_state_.peekState();

	std::cout << "State : " << static_cast<int>(cur_gs_) << std::endl;

	switch (cur_gs_) {

		case STATE::GS_Loading: break;

		case STATE::GS_Menu: break;

		case STATE::GS_Running:
		case STATE::GS_MovingRight:
		case STATE::GS_MovingLeft:
		case STATE::GS_Jumping:

			for (const auto item : ev_list) {
				std::cout << "Item tag: " << item->GetTag() << std::endl;
				item->onUpdate(delta);
			}

			break;

		default: break;

	}

	view_cam.SetPosition({mario->GetPosition().x - (width / 2), view_cam.GetPosition().y});
	MarioWorld->Step(delta, 8, 3);

}

void Game::onRender() {
	Graphics::Render::BeginScene(view_cam);

	for (auto &item : event_handler.getEventsList()) {
		item->onRender();
	}

	Graphics::Render::EndScene();
}

void Game::LoadAllShader() {

	Graphics::Shader::LoadShader("sprite", "Resources/Shader/Sprite.vert.glsl", "Resources/Shader/Sprite.frag.glsl");
	Graphics::Shader::LoadShader("flat",
								 "Resources/Shader/FlatColor.vert.glsl",
								 "Resources/Shader/FlatColor.frag.glsl");

}
void Game::LoadAllTexture() {

	// Mario
	Graphics::Texture::LoadTexture("mario-idle", "Resources/Texture/Mario/mario-idle.png", true);
	Graphics::Texture::LoadTexture("mario-run-0", "Resources/Texture/Mario/mario-run0.png", true);
	Graphics::Texture::LoadTexture("mario-run-1", "Resources/Texture/Mario/mario-run1.png", true);
	Graphics::Texture::LoadTexture("mario-run-2", "Resources/Texture/Mario/mario-run2.png", true);
	Graphics::Texture::LoadTexture("mario-jump", "Resources/Texture/Mario/mario-jump.png", true);

	// Ground
	Graphics::Texture::LoadTexture("ground", "Resources/Texture/ground.png", true);

	// Bad Mushroom
	Graphics::Texture::LoadTexture("mushroom-run-0", "Resources/Texture/Mushroom/mushroom-run0.png", true);
	Graphics::Texture::LoadTexture("mushroom-run-1", "Resources/Texture/Mushroom/mushroom-run1.png", true);
	Graphics::Texture::LoadTexture("mushroom-dead", "Resources/Texture/Mushroom/mushroom-dead.png", true);

	// Brick
	Graphics::Texture::LoadTexture("brick-0", "Resources/Texture/Brick/brick-0.png", true);
	Graphics::Texture::LoadTexture("brick-1", "Resources/Texture/Brick/brick-1.png", true);
	Graphics::Texture::LoadTexture("brick-2", "Resources/Texture/Brick/brick-2.png", true);

	// Coin Brick
	Graphics::Texture::LoadTexture("coin-brick-idle", "Resources/Texture/CoinBrick/coin-brick.png", true);
	Graphics::Texture::LoadTexture("coin-brick-break", "Resources/Texture/CoinBrick/coin-break-brick.png", true);

	// Coin
	Graphics::Texture::LoadTexture("coin-0", "Resources/Texture/Coin/coin-0.png", true);
	Graphics::Texture::LoadTexture("coin-1", "Resources/Texture/Coin/coin-1.png", true);
	Graphics::Texture::LoadTexture("coin-2", "Resources/Texture/Coin/coin-2.png", true);
	Graphics::Texture::LoadTexture("coin-3", "Resources/Texture/Coin/coin-3.png", true);
	Graphics::Texture::LoadTexture("coin-4", "Resources/Texture/Coin/coin-4.png", true);
	Graphics::Texture::LoadTexture("coin-5", "Resources/Texture/Coin/coin-5.png", true);

	// Pipe
	Graphics::Texture::LoadTexture("pipe", "Resources/Texture/pipe.png", true);

	// Stair Brick
	Graphics::Texture::LoadTexture("stair_brick", "Resources/Texture/StairBrick.png", true);

}

Game::~Game() {
	Graphics::Render::onShutDown();

	delete contact_listener;
	delete level;

	delete MarioWorld; //TODO:  Refactor to smart pointer

}
void Game::key_callback_(GLFWwindow *window, int key, int scancode, int action, int mods) {

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (key >= 0 && key < 1024 && action == GLFW_PRESS) {
		Input::keys[key] = true;
	}

	if (key >= 0 && key < 1024 && action == GLFW_RELEASE) {
		Input::keys[key] = false;
		Input::keyUp[key] = false;
	}

}
void Game::framebuffer_size_callback_(GLFWwindow *window, int width, int height) {

	glViewport(0, 0, width, height);

}
void Game::processInput(float delta) {

	if (Input::keys[GLFW_KEY_ESCAPE]) { //Pause
		game_state_.pushState(STATE::GS_Paused);
	}

	if (Input::keys[GLFW_KEY_W] or Input::keys[GLFW_KEY_SPACE]) {
		game_state_.pushState(STATE::GS_Jumping);
	}

	if (Input::keys[GLFW_KEY_A] or Input::keys[GLFW_KEY_LEFT]) {
		game_state_.pushState(STATE::GS_MovingLeft);
	}

	if (Input::keys[GLFW_KEY_D] or Input::keys[GLFW_KEY_RIGHT]) {
		game_state_.pushState(STATE::GS_MovingRight);
	}

}

} // namespace Game
