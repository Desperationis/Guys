#include "NumberButton.h"
#include "../../InputSystem.h"

Font* NumberButton::font = nullptr;
Font* NumberButton::numberFont = nullptr;
Timer NumberButton::fast;

NumberButton::NumberButton(const char* text, int x, int y, int w, int h, int& value) {
	if (font == nullptr) {
		SDL_Color tmp = SDL_Color{ 0,0,0, 255 };
		font = new Font("Fonts/8bitoperator_jve.ttf", 32, tmp);
		font->loadRenderType(Font::SOLID);
	}
	if (numberFont == nullptr) {
		SDL_Color tmp = SDL_Color{ 0,0,0, 255 };
		numberFont = new Font("Fonts/8bitoperator_jve.ttf", 24, tmp);
		numberFont->loadRenderType(Font::BLENDED);
	}
	rect.setup(x, y, w, h);
	this->value = &value;
	pastValue = value;

	this->text = font->toText(text);
	SDL_QueryTexture(this->text, NULL, NULL, &textDest.w, &textDest.h);
	textDest.x = rect.dest.x + (rect.dest.w / 2) - (textDest.w / 2);
	textDest.y = rect.dest.y + (rect.dest.h / 2) - (textDest.h / 2);

	right = font->toText(">");
	SDL_QueryTexture(right, NULL, NULL, &rightRect.dest.w, &rightRect.dest.h);

	left = font->toText("<");
	SDL_QueryTexture(left, NULL, NULL, &leftRect.dest.w, &leftRect.dest.h);

	loaded = w;

	renderValue();
}

void NumberButton::update() {
	if (loaded != rect.dest.w) {
		renderValue();

		rightRect.dest.x = rect.dest.x + rect.dest.w - (rightRect.dest.w / 2) - 20;
		rightRect.dest.y = rect.dest.y + (rect.dest.h / 2) - (rightRect.dest.h / 2);
		rightRect.update();
		leftRect.dest.x = rect.dest.x + 20;
		leftRect.dest.y = rect.dest.y + (rect.dest.h / 2) - (leftRect.dest.h / 2);
		leftRect.update();

		loaded = rect.dest.w;
	}


	if (rightRect.CollidePoint(InputSystem::mouse[InputSystem::X], InputSystem::mouse[InputSystem::Y]) && InputSystem::mouse[InputSystem::LEFT] && !pressed) {
		*value += 1;
	}
	if (*value != 0) {
		if (leftRect.CollidePoint(InputSystem::mouse[InputSystem::X], InputSystem::mouse[InputSystem::Y]) && InputSystem::mouse[InputSystem::LEFT] && !pressed) {
			*value -= 1;
		}
	}
	if (pastValue != *value) {
		pastValue = *value;
		renderValue();
	}
	pressed = rect.CollidePoint(InputSystem::mouse[InputSystem::X], InputSystem::mouse[InputSystem::Y]) && InputSystem::mouse[InputSystem::LEFT];
	if (pressed) {
		if (!fast.isStarted()) {
			fast.start();
		}
	}
	if (!InputSystem::mouse[InputSystem::LEFT]) {
		fast.stop();
	}
	if (fast.getTicks() > 400) {
		pressed = false;
	}
}

void NumberButton::renderValue() {
	std::stringstream tmp; tmp << *value;
	if (currentValue) {
		SDL_DestroyTexture(currentValue);
	}
	currentValue = numberFont->toText(tmp.str().c_str());
	SDL_QueryTexture(currentValue, NULL, NULL, &currentValueRect.w, &currentValueRect.h);
	currentValueRect.y = textDest.y + textDest.h;
	currentValueRect.x = rect.dest.x + (rect.dest.w / 2) - (currentValueRect.w / 2);
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
	TM::DrawTexture(right, rightRect.dest);
	TM::DrawTexture(left, leftRect.dest);
}

void NumberButton::clean() {
	SDL_DestroyTexture(text);

	SDL_DestroyTexture(currentValue);
	SDL_DestroyTexture(right);
	SDL_DestroyTexture(left);
}
