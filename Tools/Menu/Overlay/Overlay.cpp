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


#include "Overlay.h"
#include "../../../Setup.h"
#include "../../../Game.h"
#include "BoolButton.h"
#include "NumberButton.h"
#include "../Dropdown.h"

bool dummy = false;

Overlay::Overlay() {
	dest = SDL_Rect{ 10,10, WINDOW::WIDTH, 100 };
	init();
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

void Overlay::init() {
	int number = 5;
	int margin = 8;
	int width = (dest.w / number);

	for (int i = 0; i < buttons.size(); i++) {
		buttons[i]->clean();
		delete buttons[i];
	}

	buttons.clear();

	buttons.push_back(new BoolButton("Reset", width * 0, 0, width, 90, HOOMAN::RESET, true));
	buttons.push_back(new Dropdown("Quadtree", width * 1, 0, width, 90));

	buttons.back()->addButton(new BoolButton("Render", -1, -1, -1, -1, QUADTREE::RENDER));
	buttons.back()->addButton(new NumberButton("Iterations", -1, -1, -1, -1, QUADTREE::MAX_ITERATION));


	buttons.push_back(new Dropdown("Food", width * 2, 0, width, 90));

	buttons.back()->addButton(new NumberButton("Initial Count", -1, -1, -1, -1, FOOD::BEGIN));
	buttons.back()->addButton(new NumberButton("Growth Time Interval", -1, -1, -1, -1, FOOD::GROWTH));
	buttons.back()->addButton(new NumberButton("Plants Per Growth", -1, -1, -1, -1, FOOD::MULTIPLIER));
	buttons.back()->addButton(new NumberButton("Size", -1, -1, -1, -1, FOOD::SIZE));

	buttons.push_back(new Dropdown("Guys", width * 3, 0, width, 90));

	buttons.back()->addButton(new NumberButton("Initial Count", -1, -1, -1, -1, HOOMAN::BEGIN));
	buttons.back()->addButton(new NumberButton("Sight", -1, -1, -1, -1, HOOMAN::SIGHT));
	buttons.back()->addButton(new BoolButton("Render Sight", -1, -1, -1, -1, HOOMAN::RENDER_SIGHT));
	buttons.back()->addButton(new NumberButton("Size", -1, -1, -1, -1, HOOMAN::SIZE));


	buttons.push_back(new Dropdown("Graphics", width * 4, 0, width, 90));

	buttons.back()->addButton(new BoolButton("VSync", -1, -1, -1, -1, WINDOW::VSYNC));
	buttons.back()->addButton(new BoolButton("FPS Counter", -1, -1, -1, -1, WINDOW::FPS_COUNTER));
	buttons.back()->addButton(new NumberButton("FPS", -1, -1, -1, -1, WINDOW::FPS));
}
