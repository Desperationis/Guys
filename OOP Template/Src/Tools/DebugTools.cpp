#include "DebugTools.h"
#include "../Quadtree.h"
#include "../Game.h"
#include "InputSystem.h"


void DebugTools::update() {
	x = InputSystem::mouse[InputSystem::MOUSE::X];
	y = InputSystem::mouse[InputSystem::MOUSE::Y];

	if (InputSystem::mouse[InputSystem::MOUSE::LEFT] && !Lclicked)
		Game::quadtree->insert(x, y, Game::quadtree->root, Quadtree::FOOD);
	if (InputSystem::mouse[InputSystem::MOUSE::RIGHT] && !Rclicked)
		Game::quadtree->insert(x, y, Game::quadtree->root, Quadtree::HOOMAN);
	Lclicked = InputSystem::mouse[InputSystem::MOUSE::LEFT];
	Rclicked = InputSystem::mouse[InputSystem::MOUSE::RIGHT];

	char type = '-';
	if (InputSystem::keys[SDL_SCANCODE_LSHIFT] && Lshift) {
		std::cout << "Input X: ", std::cin >> x, std::cout << "\n";
		std::cout << "Input y: ", std::cin >> y, std::cout << "\n";
		do {
			std::cout << "Type [F / H]: ", std::cin >> type, std::cout << "\n";
			switch (type) {
			case 'H':
				Game::quadtree->insert(x, y, Game::quadtree->root, Quadtree::HOOMAN);
				break;
			case 'F':
				Game::quadtree->insert(x, y, Game::quadtree->root, Quadtree::FOOD);
				break;
			default:
				std::cout << "Didn't quite catch that.\n" << std::endl;
				break;
			}
		} while (type != 'F' && type != 'H');
	}
	Lshift = InputSystem::keys[SDL_SCANCODE_LSHIFT];

	if (InputSystem::keys[SDL_SCANCODE_GRAVE]) {
		Game::quadtree->clear(Game::quadtree->root);
	}
}