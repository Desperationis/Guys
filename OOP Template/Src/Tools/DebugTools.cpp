#include "DebugTools.h"
#include "../Quadtree.h"
#include "../Game.h"
#include "InputSystem.h"


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


	if (InputSystem::keys[SDL_SCANCODE_GRAVE]) {
		Game::quadtree->clear(Game::quadtree->root);
	}
}