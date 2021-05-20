#pragma once
#include "SDL.h"
#include "../../../includes.h"
#include "../../Font.h"
#include "../../Rect.h"
#include "../../Timer.h"
#include "Button.h"

struct NumberButton : public Button {
	NumberButton(const char* text, int x, int y, int w, int h, int& value);
	void update() override;
	void render() override;
	void clean() override;
	void renderValue();


	SDL_Texture* currentValue = nullptr;
	SDL_Texture* left = nullptr;
	SDL_Texture* right = nullptr;
	SDL_Rect currentValueRect;
	Rect leftRect, rightRect;

	static Font* font;
	static Font* numberFont;
	static Timer fast;
	int* value;
	int pastValue = 0, loaded = 0;
};
