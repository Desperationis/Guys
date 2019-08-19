#include "BoolButton.h"
#include "Tools/InputSystem.h"

Font* BoolButton::font = nullptr;;

BoolButton::BoolButton(const char* text, int x, int y, int w, int h, bool& value){
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

void BoolButton::update() {
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
}