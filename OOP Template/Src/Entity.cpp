#include "Entity.h"
#include "Quadtree.h"
#include "Setup.h"
#include "Game.h"
#include "limits.h"
#include "includes.h"

Uint64 Entity::counter = 0;

Entity::Entity(int x, int y) {
	id = Entity::counter;
	rect = Rect(x, y, FOOD::SIZE, FOOD::SIZE);
	color = SDL_Color{ static_cast<Uint8>(rand() % 256), static_cast<Uint8>(rand() % 256), static_cast<Uint8>(rand() % 256), 255};
	speed = ((rand() % 100) / 10.0f) + 1.0f;
	sight = HOOMAN::SIGHT / speed;
}

bool Entity::update() {
	if (plant) { return dead; }

	bool decompose = look();

	if (rect.left < 0) {
		rect.dest.x = 0;
		rect.update();
		angle += 90;
	}
	if (rect.right > WINDOW::WIDTH) {
		rect.dest.x = WINDOW::WIDTH - rect.dest.w;
		rect.update();
		angle += 90;
	}
	if (rect.top < 0) {
		rect.dest.y = 0;
		rect.update();
		angle += 90;
	}
	if (rect.bottom > WINDOW::HEIGHT) {
		rect.dest.y = WINDOW::HEIGHT - rect.dest.h;
		rect.update();
		angle += 90;
	}

	bool f = false;
	if (!dead) {
		for (auto it = parent->entities.begin(); it != parent->entities.end(); it++) {
			if (!it.value().plant && it.value().id != id) {
				if (rect.CollideRect(it.value().rect) ) {
					if (energy >= it.value().energy && !it.value().dead) {
						it.value().dead = true;
					}
				}
			}
		}

		makeBabbe();
	}

	eyes.dest.x = static_cast<int>(rect.center[0] - (sight / 2));
	eyes.dest.y = static_cast<int>(rect.center[1] - (sight / 2));
	eyes.dest.w = static_cast<int>(sight);
	eyes.dest.h = static_cast<int>(sight);

	eyes.update();

	if (decompose) {
		dead = true;
	}

	relocate = !parent->rect.CollideRect(rect);

	return dead || relocate;
}

bool Entity::look() {
	search(Game::quadtree->root);

	int lowest = INT_MAX;

	closest = nullptr;

	if (!closest) {

		for (unsigned int i = 0; i < searches.size(); i++) {
			for (auto it = searches[i]->entities.begin(); it != searches[i]->entities.end(); it++) {
				int distance = abs(it.value().rect.center[0] - rect.center[0]) + abs(it.value().rect.center[1] - rect.center[1]);
				if (it.value().plant && !it.value().dead) {
					if (it.value().rect.CollideRect(eyes) && distance < lowest) {
						lowest = distance;
						closest = &it.value();
						roam = false;
					}
				}
			}
		}

		for (unsigned int i = 0; i < searches.size(); i++) {
			searches[i] = nullptr;
		}
	}


	searches.clear();
	if (closest) {

		rect.bufferx += static_cast<float>(cos(atan2(closest->rect.center[1] - rect.center[1], closest->rect.center[0] - rect.center[0])) * speed);
		rect.buffery += static_cast<float>(sin(atan2(closest->rect.center[1] - rect.center[1], closest->rect.center[0] - rect.center[0])) * speed);
		rect.dest.x = static_cast<int>(rect.bufferx);
		rect.dest.y = static_cast<int>(rect.buffery);
		rect.update();
		
		if (closest->rect.CollideRect(rect)) {
			energy += FOOD::ENERGY;
			closest->dead = true;
			closest = nullptr;
		}
	}

	if (!closest) {
		if (!roam) {
			angle = (rand() % 36000) / 100.0f;
			roam = true;
		}

		rect.bufferx += static_cast<float>(cos(angle * (M_PI / 180)) * speed);
		rect.buffery += static_cast<float>(sin(angle * (M_PI / 180)) * speed);
		rect.dest.x = static_cast<int>(rect.bufferx);
		rect.dest.y = static_cast<int>(rect.buffery);
		rect.update();
	}

	energy -= speed * speed * 0.5f;

	if (energy <= 0) {
		dead = true;
		return true;
	}

	return false;

}

void Entity::makeBabbe() {
	if (energy - 1000 >= 500) {
		int angle_ = (rand() % 360);
		int x = static_cast<int>((cos(angle_ * (M_PI / 180.0f)) * sight) + rect.dest.x);
		int y = static_cast<int>((sin(angle_ * (M_PI / 180.0f)) * sight) + rect.dest.y);
		Entity e(x, y);
		
		e.energy = 300;
		e.dead = dead;
		e.plant = plant;
		e.color = color;
		e.speed = speed;
		e.sight = sight;
		e.angle = angle;
		e.roam = roam;
		e.id = Entity::counter;

		energy -= 1000;
		Game::quadtree->queue.push_back(e);
	}
}

void Entity::copy(Entity& entity) {
	eyes = entity.eyes;
	rect = entity.rect;
	dead = entity.dead;
	plant = entity.plant;
	color = entity.color;
	speed = entity.speed;
	energy = entity.energy;
	sight = entity.sight;
	angle = entity.angle;
	roam = entity.roam;
	id = Entity::counter;
}

void Entity::render() {
	if (plant) {
		rect.renderFill(0, 155, 0, 255);
	}
	else {
		rect.renderFill(color);
		//eyes.renderOutline(0, 155, 155);
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
