#include "Quadtree.h"
#include "Setup.h"
#include "Food.h"

Quad::Quad(int x, int y, int w, int h) {
	rect.dest.x = x;
	rect.dest.y = y;
	rect.dest.w = w;
	rect.dest.h = h;
	rect.update();
}

Quad::~Quad() {
	parent = nullptr;
}

Quadtree::Quadtree() {
	root = new Quad(0, 0, WINDOW::WIDTH, WINDOW::HEIGHT);
}

void Quadtree::insert(int x, int y, Quad* root) {
	Quad* quad = search(x, y, root);
	SDL_Rect& dest = quad->rect.dest;
	quad->foods[Food::counter] = Food(x,y);
	quad->foods[Food::counter].parent = quad;
	Food::counter++;

	if (quad->foods.size() >= 4) {
		quad->children.push_back(Quad(dest.x, dest.y, dest.w / 2, dest.h / 2));
		quad->children.push_back(Quad(dest.x + (dest.w / 2), dest.y, dest.w / 2, dest.h / 2));
		quad->children.push_back(Quad(dest.x, dest.y + (dest.h / 2), dest.w / 2, dest.h / 2));
		quad->children.push_back(Quad(dest.x + (dest.w / 2), dest.y + (dest.h / 2), dest.w / 2, dest.h / 2));

		for (unsigned int i = 0; i < quad->children.size(); i++) {
			quad->children[i].parent = quad;
		}

		for (auto it = quad->foods.begin(); it != quad->foods.end(); it++) {
			for (unsigned int i = 0; i < quad->children.size(); i++) {
				//change to collide rect for higher accuracy over performance
				if (quad->children[i].rect.CollidePoint(it.value().rect->dest.x, it.value().rect->dest.y)) {
					insert(it.value().rect->dest.x, it.value().rect->dest.y, &quad->children[i]);
					it.value().clean();
					break;
				}

			}
		}
		quad->foods.clear();
	}
	quad = nullptr;
}

void Quadtree::insert(int x, int y, SDL_Color color, Quad* root) {
	Quad* quad = search(x, y, root);
	SDL_Rect& dest = quad->rect.dest;
	quad->people[Hooman::counter] = Hooman(x, y, color);
	quad->people[Hooman::counter].parent = quad;
	Hooman::counter++;

	if (quad->people.size() >= 4) {
		quad->children.push_back(Quad(dest.x, dest.y, dest.w / 2, dest.h / 2));
		quad->children.push_back(Quad(dest.x + (dest.w / 2), dest.y, dest.w / 2, dest.h / 2));
		quad->children.push_back(Quad(dest.x, dest.y + (dest.h / 2), dest.w / 2, dest.h / 2));
		quad->children.push_back(Quad(dest.x + (dest.w / 2), dest.y + (dest.h / 2), dest.w / 2, dest.h / 2));

		for (unsigned int i = 0; i < quad->children.size(); i++) {
			quad->children[i].parent = quad;
		}

		for (auto it = quad->people.begin(); it != quad->people.end(); it++) {
			for (unsigned int i = 0; i < quad->children.size(); i++) {
				//change to collide rect for higher accuracy over performance
				if (quad->children[i].rect.CollidePoint(it.value().rect->dest.x, it.value().rect->dest.y)) {
					insert(it.value().rect->dest.x, it.value().rect->dest.y, color, &quad->children[i]);
					it.value().clean();
					break;
				}

			}
		}
		quad->people.clear();
	}
	quad = nullptr;
}

Quad* Quadtree::search(int x, int y, Quad* root) {

	for (unsigned int i = 0; i < root->children.size(); i++) {
		if (root->children[i].rect.CollidePoint(x, y)) {
			return search(x, y, &root->children[i]);
		}
	}
	
	return root;
}

void Quadtree::update(Quad* root) {
	for (auto it = root->people.begin(); it != root->people.end(); it++) {
		if (it.value().update()) {
			queue.push_back(&it.value());
		}
	}

	for (unsigned int id = 0; id < root->children.size(); id++) {
		update(&root->children[id]);
	}
}

void Quadtree::erase(Food* food) {
	Quad* quad = search(food->rect->dest.x, food->rect->dest.y, food->parent);
	food->clean();
	quad->foods.erase(food->id);
	food = nullptr;

	int sum = 0;
	for (unsigned int i = 0; i < quad->parent->children.size(); i++) {
		sum += quad->parent->children[i].foods.size();
	}

	if (sum < 4) {
		for (unsigned int i = 0; i < quad->parent->children.size(); i++) {
			for (auto it = quad->parent->children[i].foods.begin(); it != quad->parent->children[i].foods.end(); it++) {
				quad->parent->foods[it.key()] = it.value();
				quad->parent->foods[it.key()].parent = quad;
			}
		}
		quad->parent->children.clear();
	}
	quad = nullptr;
}

void Quadtree::erase(Hooman* human) {
	Quad* quad = search(human->rect->dest.x, human->rect->dest.y, human->parent);
	human->clean();
	quad->people.erase(human->id);
	human = nullptr;

	int sum = 0;
	for (unsigned int i = 0; i < quad->parent->children.size(); i++) {
		sum += quad->parent->children[i].foods.size();
	}

	if (sum < 4) {
		for (unsigned int i = 0; i < quad->parent->children.size(); i++) {
			for (auto it = quad->parent->children[i].foods.begin(); it != quad->parent->children[i].foods.end(); it++) {
				quad->parent->foods[it.key()] = it.value();
				quad->parent->foods[it.key()].parent = quad;
			}
		}
		quad->parent->children.clear();
	}
	quad = nullptr;
}

void Quadtree::render(Quad* root) {
	root->rect.renderOutline(255, 0, 0);
	for (auto it = root->foods.begin(); it != root->foods.end(); it++) {
		it.value().render();
	}
	for (auto it = root->people.begin(); it != root->people.end(); it++) {
		it.value().render();
	}
	for (unsigned int id = 0; id < root->children.size(); id++) {
		render(&root->children[id]);
	}
}