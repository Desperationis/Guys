#include "Overlay.h"
#include "Setup.h"
#include "Game.h"
#include "Button.h"

bool dummy = false;

Overlay::Overlay() {
	dest = SDL_Rect{ 10,10, WINDOW::WIDTH, 100 };

	int number = 5;
	int margin = 8;
	int width = (dest.w / number) ;

	buttons.push_back(Button("Reset", width * 0, 0, width, 90, QUADTREE::RENDER));

	buttons.push_back(Button("Quadtree", width * 1, 0, width, 90, dummy));

	buttons.back().addButton("text");

	buttons.push_back(Button("Food", width * 2, 0, width, 90, dummy));
	buttons.push_back(Button("Hoomen", width * 3, 0, width, 90, dummy));
	buttons.push_back(Button("Graphics", width * 4, 0, width, 90, dummy));
}

void Overlay::render() {
	if (visible) {

		for (int i = 0; i < buttons.size(); i++) {
			buttons[i].render();
		}
	}
}

void Overlay::update() {
	if (InputSystem::keys[SDL_SCANCODE_TAB] && !toggle) {
		visible = !visible;
	}
	toggle = InputSystem::keys[SDL_SCANCODE_TAB];

	if (visible) {
		for (int i = 0; i < buttons.size(); i++) {
			buttons[i].update();
		}
	}
}