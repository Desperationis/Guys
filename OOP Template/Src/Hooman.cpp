#include "Hooman.h"
#include "Tools/Rect.h"
#include "Quadtree.h"

Uint32 Hooman::counter = 0;

Hooman::Hooman(int x, int y, SDL_Color& _color) {
	id = Hooman::counter;
	rect = new Rect(x, y, 5, 5);
	color = _color;
}

void Hooman::update() {
	rect->dest.x += 1;
	parent->rect.CollideRect(*rect);
	rect->update();
}

void Hooman::render() {
	rect->renderFill(color);
}

void Hooman::clean() {
	parent = nullptr;
	delete rect;
	rect = nullptr;
}