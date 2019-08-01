#include "Hooman.h"
#include "Quadtree.h"

Uint32 Hooman::counter = 0;

Hooman::Hooman(int x, int y, SDL_Color& _color) {
	id = Hooman::counter;
	rect = Rect(x, y, 5, 5);
	color = _color;
}

bool Hooman::update() {
	rect.dest.x += 1;
	rect.update();
	dead = !parent->rect.CollideRect(rect);

	return dead;
}

void Hooman::render() {
	rect.renderFill(color);
}

void Hooman::clean() {
	parent = nullptr;
}