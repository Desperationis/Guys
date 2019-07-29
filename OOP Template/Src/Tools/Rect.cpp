#include "Rect.h"
#include "FRect.h"

Rect::Rect() {
	left = right = top = bottom = 0;
	dest.x = dest.w = dest.y = dest.h = 0;
	center[0] = 0;
	center[1] = 0;
}

Rect::Rect(const int x, const int y, const int w, const int h) {
	setup(x, y, w, h);
}


bool Rect::CollideRect(const Rect& target) const {
	return (left < target.right &&
			right > target.left &&
			bottom > target.top &&
			top < target.bottom);
}

bool Rect::CollideRect(const FRect& target) const {
	return ((float)left < target.right &&
			(float)right > target.left &&
			(float)bottom > target.top &&
			(float)top < target.bottom);
}

bool Rect::CollidePoint(const int x, const int y) const {
	return (x < right && x > left && y < bottom && y > top);
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