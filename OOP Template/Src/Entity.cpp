#include "Entity.h"
#include "Quadtree.h"
#include "Setup.h"
#include "Game.h"
#include "limits.h"
#include "includes.h"

Uint32 Entity::counter = 0;

Entity::Entity(int x, int y) {
	id = Entity::counter;
	rect = Rect(x, y, FOOD::SIZE, FOOD::SIZE);
	color = SDL_Color{ static_cast<Uint8>(rand() % 256), static_cast<Uint8>(rand() % 256), static_cast<Uint8>(rand() % 256), 255};
}

bool Entity::update() {
	if (plant) return dead;

	eyes.dest.x = rect.center[0] - (HOOMAN::SIGHT / 2);
	eyes.dest.y = rect.center[1] - (HOOMAN::SIGHT / 2);
	eyes.dest.w = HOOMAN::SIGHT;
	eyes.dest.h = HOOMAN::SIGHT;

	eyes.update();

	bool decompose = look();

	if (rect.left < 0) {
		rect.dest.x = 0;
		rect.update();
	}
	if (rect.right > WINDOW::WIDTH) {
		rect.dest.x = WINDOW::WIDTH - rect.dest.w;
		rect.update();
	}
	if (rect.top < 0) {
		rect.dest.y = 0;
		rect.update();
	}
	if (rect.bottom > WINDOW::HEIGHT) {
		rect.dest.y = WINDOW::HEIGHT - rect.dest.h;
		rect.update();
	}

	if (!dead) {
		for (auto it = parent->entities.begin(); it != parent->entities.end(); it++) {
			if (!it.value().plant && it.value().id != id) {
				if (rect.CollideRect(it.value().rect) && energy > it.value().energy) {
					it.value().plant = true;
					it.value().dead = true;
				}
			}
		}
	}

	if (decompose) {
		plant = true;
		return true;
	}


	dead = !parent->rect.CollideRect(rect);
	return dead;
}

bool Entity::look() {
	search(Game::quadtree->root);

	int lowest = INT_MAX;

	closest = nullptr;

	if (!closest) {

		for (int i = 0; i < searches.size(); i++) {
			for (auto it = searches[i]->entities.begin(); it != searches[i]->entities.end(); it++) {
				int distance = abs(it.value().rect.center[0] - rect.center[0]) + abs(it.value().rect.center[1] - rect.center[1]);
				if (it.value().plant && !it.value().dead) {
					if (it.value().rect.CollideRect(eyes) && distance < lowest) {
						lowest = distance;
						closest = &it.value();
					}
				}
			}
		}

		for (int i = 0; i < searches.size(); i++) {
			searches[i] = nullptr;
		}
	}


	searches.clear();
	if (closest) {

		rect.bufferx += cos(atan2(closest->rect.center[1] - rect.center[1], closest->rect.center[0] - rect.center[0])) * speed;
		rect.buffery += sin(atan2(closest->rect.center[1] - rect.center[1], closest->rect.center[0] - rect.center[0])) * speed;
		rect.dest.x = rect.bufferx;
		rect.dest.y = rect.buffery;
		rect.update();
		
		if (closest->rect.CollideRect(rect)) {
			energy += FOOD::ENERGY;
			closest->dead = true;
			closest = nullptr;
		}
	}

	energy -= speed;

	if (energy <= 0) {
		return true;
	}

	return false;

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
	closest = nullptr;
	searches.clear();
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