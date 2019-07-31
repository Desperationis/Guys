#include "Hooman.h"
#include "Tools/Rect.h"
#include "Quadtree.h"

Uint32 Hooman::counter = 0;

Hooman::Hooman(int x, int y, SDL_Color& _color) {
	id = Hooman::counter;
	rect = new Rect(x, y, 5, 5);
	color = _color;
}

bool Hooman::update() {
	if (rect->dest.x < 780) {

		rect->dest.x += 1;
	}
	rect->update();
	return !parent->rect.CollideRect(*rect);
}

void Hooman::render() {
	rect->renderFill(color);
}

void Hooman::clean() {
	parent = nullptr;
	delete rect;
	rect = nullptr;
}