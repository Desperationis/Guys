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

Quadtree::Quadtree() {
	root = new Quad(0, 0, WINDOW::WIDTH, WINDOW::HEIGHT);
}

Food* Quadtree::insert(int x, int y, Quad* root) {
	Quad& quad = *search(x, y, root);
	SDL_Rect& dest = quad.rect.dest;
	quad.data[Food::counter] = Food(x,y);
	Food* tmp = &quad.data[Food::counter];

	if (quad.data.size() >= 4) {
		quad.children.push_back(Quad(dest.x, dest.y, dest.w / 2, dest.h / 2));
		quad.children.push_back(Quad(dest.x + (dest.w / 2), dest.y, dest.w / 2, dest.h / 2));
		quad.children.push_back(Quad(dest.x, dest.y + (dest.h / 2), dest.w / 2, dest.h / 2));
		quad.children.push_back(Quad(dest.x + (dest.w / 2), dest.y + (dest.h / 2), dest.w / 2, dest.h / 2));

		for (auto it = quad.data.begin(); it != quad.data.end(); it++) {
			for (int i = 0; i < quad.children.size(); i++) {
				//change to collide rect for higher accuracy over performance
				if (it.value().id == Food::counter) {
					tmp = &it.value();
				}
				if (quad.children[i].rect.CollidePoint(it.value().rect->dest.x, it.value().rect->dest.y)) {
					insert(it.value().rect->dest.x, it.value().rect->dest.y, &quad.children[i]);
					break;
				}

			}
		}

		quad.data.clear();
	}

	Food::counter++;
	return tmp;
}

Quad* Quadtree::search(int x, int y, Quad* root) {
	for (int i = 0; i < root->children.size(); i++) {
		if (root->children[i].rect.CollidePoint(x, y)) {
			return search(x,y , &root->children[i]);
		}
	}
	

	return root;
}

void Quadtree::erase(Food* food) {
	Quad* parent = search(food->rect->left, food->rect->top, root);

	parent->data.erase(food->id);
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