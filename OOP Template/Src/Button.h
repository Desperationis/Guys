#pragma once
#include "SDL.h"
#include "includes.h"
#include "Tools/Font.h"
#include "Tools/Rect.h"

struct Button {
	Button(const char* text, int x, int y, int w, int h, bool& value);
	void update();
	void render();
	void addButton(const char* text);

	static Font* font;
	SDL_Rect textDest;
	Rect rect;
	SDL_Texture* text;
	SDL_Color color{ 255,255,255, 240 };
	std::vector<Button*> dropDown;
	bool pressed = false;
	bool* value;
};
