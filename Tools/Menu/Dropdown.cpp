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


#include "Dropdown.h"
#include "../InputSystem.h"

Font* Dropdown::font = nullptr;

Dropdown::Dropdown(const char* text, int x, int y, int w, int h) {
	if (font == nullptr) {
		SDL_Color tmp = SDL_Color{ 0,0,0, 255 };
		font = new Font("../Fonts/8bitoperator_jve.ttf", 32, tmp);
		font->loadRenderType(Font::BLENDED);
	}
	this->text = font->toText(text);
	rect.setup(x, y, w, h);

	SDL_QueryTexture(this->text, NULL, NULL, &textDest.w, &textDest.h);
	textDest.x = rect.dest.x + (rect.dest.w / 2) - (textDest.w / 2);
	textDest.y = rect.dest.y + (rect.dest.h / 2) - (textDest.h / 2);
}

void Dropdown::update() {
	for (unsigned int i = 0; i < dropDown.size(); i++) {
		if (preview) {
			dropDown[i]->update();
		}
	}
}

void Dropdown::render() {
	TM::renderDrawColor(color);
	SDL_RenderFillRect(TM::renderer, &rect.dest);

	TM::renderDrawColor(0, 0, 0, 255);
	SDL_RenderDrawLine(TM::renderer, rect.dest.x, rect.dest.y, rect.dest.x, rect.dest.y + rect.dest.h);
	SDL_RenderDrawLine(TM::renderer, rect.dest.x + rect.dest.w, rect.dest.y, rect.dest.x + rect.dest.w, rect.dest.y + rect.dest.h);

	TM::DrawTexture(text, textDest);

	if (dropDown.size() != 0) {
		if (preview) {
			preview = false;
			for (unsigned int i = 0; i < dropDown.size(); i++) {
				preview = dropDown[i]->rect.CollidePoint(InputSystem::mouse[InputSystem::X], InputSystem::mouse[InputSystem::Y]) || preview;
			}
		}
		if (!preview) {
			preview = rect.CollidePoint(InputSystem::mouse[InputSystem::X], InputSystem::mouse[InputSystem::Y]);
		}

		if (preview) {
			for (unsigned int i = 0; i < dropDown.size(); i++) {
				dropDown[i]->render();
			}
		}
	}
}

void Dropdown::addButton(Button* button) {
	button->rect.dest = rect.dest;

	if (dropDown.size() == 0) {
		button->rect.dest.y = rect.dest.y + rect.dest.h;
	}
	else {
		button->rect.dest.y = dropDown.back()->rect.dest.y + rect.dest.h;
	}
	button->rect.update();
	button->textDest.x = button->rect.dest.x + (rect.dest.w / 2) - (button->textDest.w / 2);
	button->textDest.y = button->rect.dest.y + (rect.dest.h / 2) - (button->textDest.h / 2);
	dropDown.push_back(button);
}
