#ifndef GAME_H
#define GAME_H

#include "box2d/box2d.h"
#include "GL/glew.h"

#include "ContactListener.hpp"
#include "Entity/EntityGround.hpp"
#include "Entity/EntityMario.hpp"
#include "EventSystem.hpp"
#include "GameState.hpp"
#include "GAME_STATES.hpp"
#include "Input.hpp"
#include "interface/IEntity.hpp"
#include "interface/IEventHandler.hpp"
#include "interface/IProcessInput.hpp"
#include "Level.hpp"
//#include "Menu/MainMenu.hpp"
#include "View.hpp"

#include <GLFW/glfw3.h>
#include <memory>
#include <vector>

namespace Game {

class Game : public IProcessInput {
 public:

	Game(unsigned int width, unsigned int height);
	~Game();

	bool Run();

	void onInit();
	void onUpdate(float delta);
	void onRender();

	void processInput(float delta) override;

	static void LoadAllShader();
	static void LoadAllTexture();

	static constexpr float PIXEL_TO_M = 150.f;

 private:
	Camera view_cam;

	unsigned int width, height;

	EventSystem event_handler;

	std::shared_ptr<EntityMario> mario;
	std::shared_ptr<EntityGround> ground;
	std::shared_ptr<Level> level;

//	std::shared_ptr<MainMenu> main_menu;

	b2World *MarioWorld;

	std::shared_ptr<ContactListener> contact_listener;

	GameState &game_state_ = GameState::getInstance();

	static void key_callback_(GLFWwindow *window, int key, int scancode, int action, int mods);
	static void framebuffer_size_callback_(GLFWwindow *window, int width, int height);

};

} // namespace Game

#endif // GAME_H
