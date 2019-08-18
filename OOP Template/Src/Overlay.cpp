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

	buttons.push_back(Button("Reset", width * 0, 0, width, 90, HOOMAN::RESET));
	buttons.push_back(Button("Quadtree", width * 1, 0, width, 90, dummy));

	buttons.back().addButton("Render", QUADTREE::RENDER);
	buttons.back().addButton("Iterations", dummy);

	buttons.push_back(Button("Food", width * 2, 0, width, 90, dummy));

	buttons.back().addButton("Initial Count", dummy);
	buttons.back().addButton("Growth", dummy);
	buttons.back().addButton("Size", dummy);
	buttons.back().addButton("Color", dummy);

	buttons.push_back(Button("Hoomen", width * 3, 0, width, 90, dummy));

	buttons.back().addButton("Initial Count", dummy);
	buttons.back().addButton("Sight", dummy);
	buttons.back().addButton("Render Sight", HOOMAN::RENDER_SIGHT);
	buttons.back().addButton("Color", dummy);

	buttons.push_back(Button("Graphics", width * 4, 0, width, 90, dummy));

	buttons.back().addButton("VSync", dummy);
	buttons.back().addButton("FPS Counter", WINDOW::FPS_COUNTER);
	buttons.back().addButton("Width", dummy);
	buttons.back().addButton("Height", dummy);
}

void Overlay::render() {
	if (visible) {

		for (unsigned int i = 0; i < buttons.size(); i++) {
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
		for (unsigned int i = 0; i < buttons.size(); i++) {
			buttons[i].update();
		}
	}
}