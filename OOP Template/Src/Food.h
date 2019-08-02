#pragma once
#include "includes.h"
#include "Tools/Rect.h"

struct Quad;
struct Food {
	Food();
	Food(int x, int y);
	void render();
	void clean();

	bool dead = false;
	Quad* parent = nullptr;
	Rect rect;
	Uint32 id;
	static const int value;
	static Uint32 counter;
}; 

