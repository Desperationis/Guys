// Simulation of life written in C++ and SDL. 
// Copyright (C) 2021 Diego Contreras
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.


#include "Game.h"
#include "Tools/Timer.h"
#include "Tools/InputSystem.h"
#include "Setup.h"

int main(int argc, char* argv[])
{

	srand(static_cast<unsigned int>(time(0)));

	Game game("Guys", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW::WIDTH, WINDOW::HEIGHT, NULL);

	int countedFrames = 0;
	Timer regulator;

	while (game.isRunning()) {
		regulator.start();

		game.events();
		game.update();
		game.render();

		countedFrames++;
		if (regulator.getTicks() < static_cast<Uint32>(1000 / WINDOW::FPS)) {
			SDL_Delay((1000 / WINDOW::FPS) - regulator.getTicks());
			// 1000ms / 60 = 16ms delay for 60 fps
		}
		regulator.stop();

		if (InputSystem::keys[SDL_SCANCODE_RSHIFT]) {
			std::cout << "FRAMERATE: ";
			std::cin >> WINDOW::FPS;
			std::cout << "\n";
		}
	}


	return 0;
}
