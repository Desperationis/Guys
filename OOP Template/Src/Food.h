#pragma once
#include "includes.h"

struct Rect;
struct Quad;
struct Food {
	Food();
	void render();

	Quad* parent = nullptr;
	Rect* rect = nullptr;
	static const int value;
	Uint32 id;
	static Uint32 counter;
}; 

