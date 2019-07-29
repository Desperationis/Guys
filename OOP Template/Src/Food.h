#pragma once
#include "includes.h"

struct Rect;
struct Quad;
struct Food {
	Food();
	void render();

	Quad* parent = nullptr;
	Rect* rect = nullptr;
	Uint32 id;
	static const int value;
	static Uint32 counter;
}; 

