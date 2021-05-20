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


#include "DebugTools.h"
#include "../Quadtree.h"
#include "../Game.h"
#include "InputSystem.h"
#include "../Setup.h"


void DebugTools::update() {
	x = InputSystem::mouse[InputSystem::MOUSE::X];
	y = InputSystem::mouse[InputSystem::MOUSE::Y];

	if (InputSystem::mouse[InputSystem::MOUSE::LEFT] && !Lclicked) {
		Entity e(x, y);
		e.plant = true;
		Game::quadtree->insert(e);
	}
	if (InputSystem::mouse[InputSystem::MOUSE::RIGHT] && !Rclicked) {
		Entity e(x, y);
		Game::quadtree->insert(e);
	}
	Lclicked = InputSystem::mouse[InputSystem::MOUSE::LEFT];
	Rclicked = InputSystem::mouse[InputSystem::MOUSE::RIGHT];


	if (HOOMAN::RESET) {
		Game::quadtree->clear(Game::quadtree->root);
		for (int i = 0; i < HOOMAN::BEGIN; i++) {
			int x = (rand() % (WINDOW::WIDTH - 4)) + 2;
			int y = (rand() % (WINDOW::HEIGHT - 4)) + 2;
			Entity e(x, y);
			Game::quadtree->insert(e);
		}
		for (int i = 0; i < FOOD::BEGIN; i++) {
			int x = (rand() % (WINDOW::WIDTH - 4)) + 2;
			int y = (rand() % (WINDOW::HEIGHT - 4)) + 2;
			Entity e(x, y);
			e.plant = true;
			Game::quadtree->insert(e);
		}
		HOOMAN::RESET = false;
	}
}
