#include "Quadtree.h"
#include "Setup.h"

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

void Quadtree::render(Quad* root) {
	root->rect.renderOutline(255, 0, 0);
	for (int id = 0; id < root->children.size(); id++) {
		render(&root->children[id]);
	}
}