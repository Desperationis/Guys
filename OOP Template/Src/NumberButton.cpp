#include "NumberButton.h"
#include "Tools/InputSystem.h"

Font* NumberButton::font = nullptr;

NumberButton::NumberButton(const char* text, int x, int y, int w, int h, int& value) {
	if (font == nullptr) {
		SDL_Color tmp = SDL_Color{ 0,0,0, 255 };
		font = new Font("Fonts\\8bitoperator_jve.ttf", 32, tmp);
		font->loadRenderType(Font::SOLID);
	}
	this->text = font->toText(text);
	rect.setup(x, y, w, h);
	this->value = &value;
	pastValue = value;

	SDL_QueryTexture(this->text, NULL, NULL, &textDest.w, &textDest.h);
	textDest.x = rect.dest.x + (rect.dest.w / 2) - (textDest.w / 2);
	textDest.y = rect.dest.y + (rect.dest.h / 2) - (textDest.h / 2);

	loaded = w;

	renderValue();
}

void NumberButton::update() {
	if (loaded != rect.dest.w) {
		renderValue();
		loaded = rect.dest.w;
	}

	if (rect.CollidePoint(InputSystem::mouse[InputSystem::X], InputSystem::mouse[InputSystem::Y]) && InputSystem::mouse[InputSystem::LEFT] && !pressed) {
		//*value = !(*value);
	}
	if (pastValue != *value) {
		pastValue = *value;
		renderValue();
	}
	pressed = rect.CollidePoint(InputSystem::mouse[InputSystem::X], InputSystem::mouse[InputSystem::Y]) && InputSystem::mouse[InputSystem::LEFT];
}

void NumberButton::renderValue() {
	std::stringstream tmp; tmp << *value;
	std::cout << tmp.str() << std::endl;
	if (currentValue) {
		SDL_DestroyTexture(currentValue);
	}
	currentValue = font->toText(tmp.str().c_str());
	SDL_QueryTexture(currentValue, NULL, NULL, &currentValueRect.w, &currentValueRect.h);
	currentValueRect.y = textDest.y + textDest.h;
	currentValueRect.x = rect.dest.x + (rect.dest.w / 2) - (currentValueRect.w / 2);
	std::cout << rect.dest.w << std::endl;
}

void NumberButton::render() {
	if (pressed) {
		TM::renderDrawColor(color.r / 2, color.g / 2, color.b / 2, color.a);
	}
	else {
		TM::renderDrawColor(color);
	}
	SDL_RenderFillRect(TM::renderer, &rect.dest);

	TM::renderDrawColor(0, 0, 0, 255);
	SDL_RenderDrawLine(TM::renderer, rect.dest.x, rect.dest.y, rect.dest.x, rect.dest.y + rect.dest.h);
	SDL_RenderDrawLine(TM::renderer, rect.dest.x + rect.dest.w, rect.dest.y, rect.dest.x + rect.dest.w, rect.dest.y + rect.dest.h);

	TM::DrawTexture(text, textDest);
	TM::DrawTexture(currentValue, currentValueRect);
}