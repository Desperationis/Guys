#include "Overlay.h"
#include "Setup.h"
#include "Game.h"
#include "BoolButton.h"
#include "NumberButton.h"
#include "Dropdown.h"

bool dummy = false;

Overlay::Overlay() {
	dest = SDL_Rect{ 10,10, WINDOW::WIDTH, 100 };

	int number = 5;
	int margin = 8;
	int width = (dest.w / number) ;

	buttons.push_back(new BoolButton("Reset", width * 0, 0, width, 90, HOOMAN::RESET));
	buttons.push_back(new Dropdown("Quadtree", width * 1, 0, width, 90));

	buttons.back()->addButton(new BoolButton("Render", -1, -1, -1, -1, QUADTREE::RENDER));
	buttons.back()->addButton(new NumberButton("Iterations", -1, -1, -1, -1, QUADTREE::MAX_ITERATION));


	buttons.push_back(new Dropdown("Food", width * 2, 0, width, 90));

	buttons.back()->addButton(new BoolButton("Initial Count", -1, -1, -1, -1, dummy));
	buttons.back()->addButton(new BoolButton("Growth", -1, -1, -1, -1, dummy));
	buttons.back()->addButton(new BoolButton("Size", -1, -1, -1, -1, dummy));
	buttons.back()->addButton(new BoolButton("Color", -1, -1, -1, -1, dummy));
	
	buttons.push_back(new Dropdown("Hoomen", width * 3, 0, width, 90));
	
	buttons.back()->addButton(new BoolButton("Initial Count", -1, -1, -1, -1, dummy));
	buttons.back()->addButton(new BoolButton("Sight", -1, -1, -1, -1, dummy));
	buttons.back()->addButton(new BoolButton("Render Sight", -1, -1, -1, -1, HOOMAN::RENDER_SIGHT));
	buttons.back()->addButton(new BoolButton("Color", -1, -1, -1, -1, dummy));

	
	/*buttons.push_back(new Dropdown("Graphics", width * 4, 0, width, 90));

	buttons.back()->addButton(new BoolButton("VSync", -1, -1, -1, -1, dummy));
	buttons.back()->addButton(new BoolButton("FPS Counter", -1, -1, -1, -1, WINDOW::FPS_COUNTER));
	buttons.back()->addButton(new BoolButton("Width", -1, -1, -1, -1, dummy));
	buttons.back()->addButton(new BoolButton("Height", -1, -1, -1, -1, dummy));*/
}

void Overlay::render() {
	if (visible) {

		for (unsigned int i = 0; i < buttons.size(); i++) {
			buttons[i]->render();
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
			buttons[i]->update();
		}
	}
}