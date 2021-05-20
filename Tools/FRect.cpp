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


#include "FRect.h"
#include "Rect.h"

FRect::FRect() {
	left = right = top = bottom = 0.0f;
	dest.x = dest.w = dest.y = dest.h = 0;
	center[0] = 0.0f;
	center[1] = 0.0f;
}

FRect::FRect(const float x, const float y, const float w, const float h) {
	setup(x, y, w, h);
}


bool FRect::CollideRect(const FRect& target) const {
	return (left < target.right &&
			right > target.left &&
			bottom > target.top &&
			top < target.bottom);
}

bool FRect::CollideRect(const Rect& target) const {
	return ((int)left < target.right &&
			(int)right > target.left &&
			(int)bottom > target.top &&
			(int)top < target.bottom);
}

bool FRect::CollidePoint(const int x, const int y) const {
	return (x < right && x > left && y < bottom && y > top);
}


void FRect::renderOutline(int R = 255, int G = 0, int B = 0) const {
	SDL_SetRenderDrawColor(TM::renderer, (Uint8)R, (Uint8)G, (Uint8)B, 255);
	SDL_RenderDrawRect(TM::renderer, &dest);
}

void FRect::renderOutline(const Uint8 R = 255, const Uint8 G = 0, const Uint8 B = 0) const {
	SDL_SetRenderDrawColor(TM::renderer, R, G, B, 255);
	SDL_RenderDrawRect(TM::renderer, &dest);
}

void FRect::renderOutline(const SDL_Color& color) const {
	SDL_SetRenderDrawColor(TM::renderer, color.r, color.g, color.b, 255);
	SDL_RenderDrawRect(TM::renderer, &dest);
}

void FRect::renderFill(int R = 255, int G = 0, int B = 0, int A = 255)  const {
	SDL_SetRenderDrawColor(TM::renderer, R, G, B, A);
	SDL_RenderFillRect(TM::renderer, &dest);
}

void FRect::renderFill(const Uint8 R = 255, const Uint8 G = 0, const Uint8 B = 0, const Uint8 A = 255) const {
	SDL_SetRenderDrawColor(TM::renderer, R, G, B, A);
	SDL_RenderFillRect(TM::renderer, &dest);
}

void FRect::renderFill(const SDL_Color& color) const {
	SDL_SetRenderDrawColor(TM::renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(TM::renderer, &dest);
}

void FRect::setup(const float x, const float y, const float w, const float h) {
	dest.x = (int)x;
	dest.y = (int)y;
	dest.w = (int)w;
	dest.h = (int)h;

	left = x;
	right = x + w;
	top = y;
	bottom = y + h;

	center[0] = x + (w / 2.0f);
	center[1] = y + (h / 2.0f);
}

void FRect::update() {
	left = (float)dest.x;
	top = (float)dest.y;
	right = (float)dest.x + (float)dest.w;
	bottom = (float)dest.y + (float)dest.h;

	center[0] = left + (dest.w / 2.0f);
	center[1] = top + (dest.h / 2.0f);
}
