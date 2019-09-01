#include "BoolButton.h"
#include "../../InputSystem.h"

Font* BoolButton::font = nullptr;
Font* BoolButton::indicatorFont = nullptr;

BoolButton::BoolButton(const char* text, int x, int y, int w, int h, bool& value, bool indicatorHidden_){
	if (font == nullptr) {
		SDL_Color tmp = SDL_Color{ 0,0,0, 255 };
		font = new Font("Fonts\\8bitoperator_jve.ttf", 32, tmp);
		font->loadRenderType(Font::BLENDED);
	}
	if (indicatorFont == nullptr) {
		SDL_Color tmp = SDL_Color{ 0,0,0, 255 };
		indicatorFont = new Font("Fonts\\8bitoperator_jve.ttf", 24, tmp);
		indicatorFont->loadRenderType(Font::BLENDED);
	}
	this->text = font->toText(text);
	indicatorBool = value;
	rect.setup(x, y, w, h);
	this->value = &value;

	SDL_QueryTexture(this->text, NULL, NULL, &textDest.w, &textDest.h);
	textDest.x = rect.dest.x + (rect.dest.w / 2) - (textDest.w / 2);
	textDest.y = rect.dest.y + (rect.dest.h / 2) - (textDest.h / 2);
	indicatorHidden = indicatorHidden_;
}

void BoolButton::update() {
	if (indicatorBool != *value) {
		indicatorBool = *value;
		renderValue();
	}
	if (loaded != rect.dest.w) {
		renderValue();
		loaded = rect.dest.w;
	}

	if (rect.CollidePoint(InputSystem::mouse[InputSystem::X], InputSystem::mouse[InputSystem::Y]) && InputSystem::mouse[InputSystem::LEFT] && !pressed) {
		*value = !(*value);
	}
	pressed = rect.CollidePoint(InputSystem::mouse[InputSystem::X], InputSystem::mouse[InputSystem::Y]) && InputSystem::mouse[InputSystem::LEFT];
}

void BoolButton::render() {
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
	if (!indicatorHidden) {
		TM::DrawTexture(indicator, indicatorRect);
	}
}


void BoolButton::renderValue() {
	if (indicator) {
		SDL_DestroyTexture(indicator);
	}

	if (*value) {
		indicator = indicatorFont->toText("On");
	}
	else {
		indicator = indicatorFont->toText("Off");
	}


	SDL_QueryTexture(indicator, NULL, NULL, &indicatorRect.w, &indicatorRect.h);
	indicatorRect.y = textDest.y + textDest.h;
	indicatorRect.x = rect.dest.x + (rect.dest.w / 2) - (indicatorRect.w / 2);
}

void BoolButton::clean() {
	SDL_DestroyTexture(text);
	SDL_DestroyTexture(indicator);
}