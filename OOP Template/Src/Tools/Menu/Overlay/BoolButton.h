#pragma once
#include "SDL.h"
#include "../../../includes.h"
#include "../../Font.h"
#include "../../Rect.h"
#include "Button.h"

struct BoolButton : public Button {
	BoolButton(const char* text, int x, int y, int w, int h, bool& value, bool indicatorHidden_ = false) ;
	void update() override;
	void render() override;
	void clean() override;
	void renderValue();

	
	static Font* font;
	static Font* indicatorFont;
	bool* value;
	int loaded = -1;

	bool indicatorBool = false;
	bool indicatorHidden = false;
	SDL_Texture* indicator = nullptr;
	SDL_Rect indicatorRect;
};
