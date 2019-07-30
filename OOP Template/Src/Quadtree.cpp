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
	quad->data[Food::counter] = Food(x,y);
	quad->data[Food::counter].parent = quad;
	Food::counter++;

	if (quad->data.size() >= 4) {
		quad->children.push_back(Quad(dest.x, dest.y, dest.w / 2, dest.h / 2));
		quad->children.push_back(Quad(dest.x + (dest.w / 2), dest.y, dest.w / 2, dest.h / 2));
		quad->children.push_back(Quad(dest.x, dest.y + (dest.h / 2), dest.w / 2, dest.h / 2));
		quad->children.push_back(Quad(dest.x + (dest.w / 2), dest.y + (dest.h / 2), dest.w / 2, dest.h / 2));

		for (int i = 0; i < quad->children.size(); i++) {
			quad->children[i].parent = quad;
		}

		for (auto it = quad->data.begin(); it != quad->data.end(); it++) {
			for (int i = 0; i < quad->children.size(); i++) {
				//change to collide rect for higher accuracy over performance
				if (quad->children[i].rect.CollidePoint(it.value().rect->dest.x, it.value().rect->dest.y)) {
					insert(it.value().rect->dest.x, it.value().rect->dest.y, &quad->children[i]);
					it.value().clean();
					break;
				}

			}
		}
		quad->data.clear();
	}
}

Quad* Quadtree::search(int x, int y, Quad* root) {

	for (int i = 0; i < root->children.size(); i++) {
		if (root->children[i].rect.CollidePoint(x, y)) {
			return search(x, y, &root->children[i]);
		}
	}
	
	return root;
}

void Quadtree::erase(Food* food) {
	Quad* quad = search(food->rect->dest.x, food->rect->dest.y, root);
	food->clean();
	quad->data.erase(food->id);
	food = nullptr;

	int sum = 0;
	for (int i = 0; i < quad->parent->children.size(); i++) {
		sum += quad->parent->children[i].data.size();
	}

	if (sum < 4) {
		for (int i = 0; i < quad->parent->children.size(); i++) {
			for (auto it = quad->parent->children[i].data.begin(); it != quad->parent->children[i].data.end(); it++) {
				quad->parent->data[it.key()] = it.value();
				quad->parent->data[it.key()].parent = quad;
			}
		}
		quad->parent->children.clear();
	}
	quad = nullptr;
}

void Quadtree::render(Quad* root) {
	root->rect.renderOutline(255, 0, 0);
	for (auto it = root->data.begin(); it != root->data.end(); it++) {
		it.value().render();
	}
	for (int id = 0; id < root->children.size(); id++) {
		render(&root->children[id]);
	}
}