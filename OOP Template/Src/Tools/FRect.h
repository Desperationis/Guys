#pragma once
#include "TM.h"

//A more precise version of rect but uses more memory


struct Rect;
struct FRect {
	SDL_Rect dest;
	float right, bottom, left, top, center[2];


	FRect();
	FRect(const float x, const float y, const float w, const float h);

	// detect collision between two rects
	bool CollideRect(const Rect& target) const;
	bool CollideRect(const FRect& target) const;
	bool CollidePoint(const int x, const int y) const;

	// render the outline of a rect
	void renderOutline(const int R, const int G, const int B) const;
	void renderOutline(const Uint8 R, const Uint8 G, const Uint8 B) const;
	void renderOutline(const SDL_Color& color) const;

	//render the entire rect as one color
	void renderFill(const int R, const int G, const int B, const int A) const;
	void renderFill(const Uint8 R, const Uint8 G, const Uint8 B, const Uint8 A) const;
	void renderFill(const SDL_Color& color) const;

	//call once to initalize variables
	void setup(const float x, const float y, const float w, const float h);

	//call to update
	void update();
};