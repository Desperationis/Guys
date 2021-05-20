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


#include "Rect.h"
#include "FRect.h"

Rect::Rect() {
	left = right = top = bottom = 0;
	dest.x = dest.w = dest.y = dest.h = 0;
	bufferx = buffery = 0.0f;
	center[0] = 0;
	center[1] = 0;
}

Rect::Rect(const int x, const int y, const int w, const int h) {
	setup(x, y, w, h);
	bufferx = static_cast<float>(x);
	buffery = static_cast<float>(y);
}


bool Rect::CollideRect(const Rect& target) const {
	return (left <= target.right &&
			right >= target.left &&
			bottom >= target.top &&
			top <= target.bottom);
}

bool Rect::CollideRect(const FRect& target) const {
	return ((float)left < target.right &&
			(float)right > target.left &&
			(float)bottom > target.top &&
			(float)top < target.bottom);
}

bool Rect::CollidePoint(const int x, const int y) const {
	return (x < right && x >= left && y < bottom && y >= top);
}

void Rect::renderOutline(int R = 255, int G = 0, int B = 0) const {
	SDL_SetRenderDrawColor(TM::renderer, (Uint8)R, (Uint8)G, (Uint8)B, 255);
	SDL_RenderDrawRect(TM::renderer, &dest);
}

void Rect::renderOutline(const Uint8 R = 255, const Uint8 G = 0, const Uint8 B = 0) const {
	SDL_SetRenderDrawColor(TM::renderer, R, G, B, 255);
	SDL_RenderDrawRect(TM::renderer, &dest);
}

void Rect::renderOutline(const SDL_Color& color) const {
	SDL_SetRenderDrawColor(TM::renderer, color.r, color.g, color.b, 255);
	SDL_RenderDrawRect(TM::renderer, &dest);
}

void Rect::renderFill(int R = 255, int G = 0, int B = 0, int A = 255)  const {
	SDL_SetRenderDrawColor(TM::renderer, R, G, B, A);
	SDL_RenderFillRect(TM::renderer, &dest);
}

void Rect::renderFill(const Uint8 R = 255, const Uint8 G = 0, const Uint8 B = 0, const Uint8 A = 255) const {
	SDL_SetRenderDrawColor(TM::renderer, R, G, B, A);
	SDL_RenderFillRect(TM::renderer, &dest);
}

void Rect::renderFill(const SDL_Color& color) const {
	SDL_SetRenderDrawColor(TM::renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(TM::renderer, &dest);
}

void Rect::setup(const int x, const int y, const int w, const int h) {
	dest.x = x;
	dest.y = y;
	dest.w = w;
	dest.h = h;

	left = x;
	right = x + w;
	top = y;
	bottom = y + h;

	center[0] = x + (w / 2);
	center[1] = y + (h / 2);

}

void Rect::update() {
	left = dest.x;
	top = dest.y;
	right = dest.x + dest.w;
	bottom = dest.y + dest.h;

	center[0] = left + (dest.w / 2);
	center[1] = top + (dest.h / 2);
}
