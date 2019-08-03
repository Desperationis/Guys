#include "Entity.h"
#include "Quadtree.h"
#include "Setup.h"

Uint32 Entity::counter = 0;

Entity::Entity(int x, int y, SDL_Color _color) {
	id = Entity::counter;
	rect = Rect(x, y, FOOD::SIZE, FOOD::SIZE);
	color = _color;
}

bool Entity::update() {
	if (plant) return dead;

	rect.dest.x += 1;
	rect.update();
	dead = !parent->rect.CollideRect(rect);

	return dead;
}

void Entity::render() {
	if (plant) {
		rect.renderFill(0, 155, 0, 255);
	}
	else {
		rect.renderFill(color);
	}
}

void Entity::clean() {
	parent = nullptr;
}