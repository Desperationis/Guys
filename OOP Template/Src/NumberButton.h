#pragma once
#include "SDL.h"
#include "includes.h"
#include "Tools/Font.h"
#include "Tools/Rect.h"
#include "Button.h"

struct NumberButton : public Button {
	NumberButton(const char* text, int x, int y, int w, int h, int& value);
	void update() override;
	void render() override;
	void renderValue();


	SDL_Texture* currentValue = nullptr;
	SDL_Rect currentValueRect;

	static Font* font;
	int* value;
	int pastValue = 0, loaded = 0;
};
