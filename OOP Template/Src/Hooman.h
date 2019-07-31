#pragma once
#include "SDL.h"

struct Rect;
struct Quad;
struct Hooman {
	Hooman() {};
	Hooman(int x, int y, SDL_Color& _color);
	bool update();
	void render();
	void clean();

	static Uint32 counter;

	Uint32 id = 0;
	Rect* rect;
	Quad* parent = nullptr;
	SDL_Color color;
};