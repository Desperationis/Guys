// Absolute ECS Template.cpp : This file contains the 'main' function. Program execution begins and ends there.
// 

#include "Game.h"
#include "Tools/Timer.h"
#include "Tools/InputSystem.h"
#include "Setup.h"

int main(int argc, char* argv[])
{
	int FRAMERATE = WINDOW::FPS;

	srand(static_cast<unsigned int>(time(0)));

	Game game("Contradictory", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW::WIDTH, WINDOW::HEIGHT, NULL);

	int countedFrames = 0;
	Timer regulator;

	while (game.isRunning()) {
		regulator.start();

		game.events();
		game.update();
		game.render();

		countedFrames++;
		if (regulator.getTicks() < 1000 / WINDOW::FPS) {
			SDL_Delay((1000 / FRAMERATE) - regulator.getTicks());
			// 1000ms / 60 = 16ms delay for 60 fps
		}
		regulator.stop();

		if (InputSystem::keys[SDL_SCANCODE_RSHIFT]) {
			std::cout << "FRAMERATE: ";
			std::cin >> FRAMERATE;
			std::cout << "\n";
		}
	}


	return 0;
}
