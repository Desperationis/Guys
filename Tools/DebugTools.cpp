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