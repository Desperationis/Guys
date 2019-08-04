#include "Entity.h"
#include "Quadtree.h"
#include "Setup.h"
#include "Game.h"

Uint32 Entity::counter = 0;

Entity::Entity(int x, int y, SDL_Color _color) {
	id = Entity::counter;
	rect = Rect(x, y, FOOD::SIZE, FOOD::SIZE);
	color = _color;
}

bool Entity::update() {
	if (plant) return dead;
	


	rect.update();

	eyes.dest.x = rect.dest.x - 50;
	eyes.dest.y = rect.dest.y - 50;
	eyes.dest.w = 100;
	eyes.dest.h = 100;


	eyes.update();
	dead = !parent->rect.CollideRect(rect);
	search(Game::quadtree->root);

	int lowest = 1000000;
	Entity* entity = nullptr;
	bool found = false;

	for (int i = 0; i < searches.size(); i++) {
		for (auto it = searches[i]->entities.begin(); it != searches[i]->entities.end(); it++) {
			if (it.value().plant) {
				if (it.value().rect.CollideRect(eyes) && abs(it.value().rect.dest.x - rect.dest.x) +
					abs(it.value().rect.dest.y - rect.dest.y) < lowest) {
					lowest = abs(it.value().rect.dest.x - rect.dest.x) +
						abs(it.value().rect.dest.y - rect.dest.y);
					entity = &it.value();
					found = true;
				}
			}
		}
	}

	for (int i = 0; i < searches.size(); i++) {
		searches[i] = nullptr;
	}

	searches.clear();
	if (found) {
		if (rect.dest.x < entity->rect.dest.x) {
			rect.dest.x += 1;
		}
		if (rect.dest.x > entity->rect.dest.x) {
			rect.dest.x -= 1;
		}
		if (rect.dest.y < entity->rect.dest.y) {
			rect.dest.y += 1;
		}
		if (rect.dest.y > entity->rect.dest.y) {
			rect.dest.y -= 1;
		}
		rect.update();

		if (entity->rect.CollideRect(rect)) {
			entity->dead = true;
		}
	}





	return dead;
}

void Entity::render() {
	if (plant) {
		rect.renderFill(0, 155, 0, 255);
	}
	else {
		rect.renderFill(color);
		eyes.renderOutline(0, 155, 155);
	}
}

void Entity::clean() {
	parent = nullptr;
}

void Entity::search(Quad* root) {
	for (unsigned int i = 0; i < root->children.size(); i++) {
		if (eyes.CollideRect(root->children[i].rect)) {
			search(&root->children[i]);
		}
	}

	if (root->entities.size() != 0) {
		searches.push_back(root);
	}
}