
#include "Game.hpp"
#include "logtest.hpp"

#include <filesystem>
#include <iostream>


int main() {

	constexpr unsigned int width = 1920, height = 1080;

	std::cout << "Current path is " << std::filesystem::current_path() << std::endl; // (1)

//	LogTest();

	Game::Game game(width, height);

	if (!game.Run()) {
		std::cerr << "Something went wrong! " << std::endl;
	};

	return 0;
}
