#include "Button.h"
#include "Tools/InputSystem.h"

Font* Button::font = nullptr;;

Button::Button(const char* text, int x, int y, int w, int h, bool& value) {
	if (font == nullptr) {
		SDL_Color tmp = SDL_Color{ 0,0,0, 255 };
		font = new Font("Fonts\\8bitoperator_jve.ttf", 32, tmp);
		font->loadRenderType(Font::BLENDED);
	}
	this->text = font->toText(text);
	rect.setup(x, y, w, h);
	this->value = &value;

	SDL_QueryTexture(this->text, NULL, NULL, &textDest.w, &textDest.h);
	textDest.x = rect.dest.x + (rect.dest.w / 2) - (textDest.w / 2);
	textDest.y = rect.dest.y + (rect.dest.h / 2) - (textDest.h / 2);
}

void Button::update() {
	if (rect.CollidePoint(InputSystem::mouse[InputSystem::X], InputSystem::mouse[InputSystem::Y]) && InputSystem::mouse[InputSystem::LEFT] && !pressed) {
		*value = !(*value);
	}
	pressed = rect.CollidePoint(InputSystem::mouse[InputSystem::X], InputSystem::mouse[InputSystem::Y]) && InputSystem::mouse[InputSystem::LEFT];

	for (unsigned int i = 0; i < dropDown.size(); i++) {
		if (preview) {
			dropDown[i]->update();
		}
	}
}

void Button::render() {
	if (pressed) {
		TM::renderDrawColor(color.r - 50, color.g - 50, color.b - 50, color.a);
	}
	else {
		TM::renderDrawColor(color);
	}
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

void Button::addButton(const char* text, bool& value) {
	if (dropDown.size() != 0) {
		dropDown.push_back(new Button(text, rect.dest.x, dropDown.back()->rect.dest.y + rect.dest.h, rect.dest.w, rect.dest.h, value));
	}
	else {
		dropDown.push_back(new Button(text, rect.dest.x, rect.dest.y + rect.dest.h, rect.dest.w, rect.dest.h, value));
	}
}