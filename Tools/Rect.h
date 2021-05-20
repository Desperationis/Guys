// Simulation of life written in C++ and SDL. 
// Copyright (C) 2021 Diego Contreras
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.


#pragma once
#include "TM.h"

struct FRect;
struct Rect
{
	SDL_Rect dest;
	int right, bottom, left, top, center[2];
	float bufferx, buffery;


	Rect();
	Rect(const int x, const int y, const int w, const int h);

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
	void setup(const int x, const int y, const int w, const int h); 

	//call to update
	void update();
};
