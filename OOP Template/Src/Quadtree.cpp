#include "Quadtree.h"
#include "Setup.h"
#include "Tools/Rect.h"

Quad::Quad(int x, int y, int w, int h) {
	boundaries.x = x;
	boundaries.y = y;
	boundaries.w = w;
	boundaries.h = h;
}

bool Quadtree::valid(const Food& food, const Quad* quad) const {
	return (food.rect->dest.x >= quad->boundaries.x &&
			food.rect->dest.x <= quad->boundaries.x + quad->boundaries.w &&
			food.rect->dest.y >= quad->boundaries.y &&
			food.rect->dest.y <= quad->boundaries.y + quad->boundaries.h);
}

Quadtree::Quadtree() {
	root = new Quad(0, 0, WINDOW::WIDTH, WINDOW::HEIGHT);
}

void Quadtree::insert(Food* food) {
	
}

Quad* Quadtree::search(const Food& food, Quad* startingQuad) const {
	for (int i = 0; i < startingQuad->quads.size(); i++) {
		if (valid(food, startingQuad->quads[i])) {
			return search(food, startingQuad->quads[i]);
		}
	}
	// if there's no children that match:
	return startingQuad;
}

const Quad* Quadtree::render(const Quad* startingQuad) const {
	SDL_RenderDrawRect(TM::renderer, &startingQuad->boundaries);
	for (int i = 0; i < startingQuad->quads.size(); i++) {
		render(startingQuad->quads[i]);
	}
	return startingQuad;
}