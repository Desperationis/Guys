#include "Quadtree.h"
#include "Setup.h"
#include "Food.h"

Quad::Quad(int x, int y, int w, int h) {
	rect.dest.x = x;
	rect.dest.y = y;
	rect.dest.w = w;
	rect.dest.h = h;
	rect.update();
	parent = nullptr;
}

Quad::~Quad() {
	parent = nullptr;
}

Quadtree::Quadtree() {
	root = new Quad(0, 0, WINDOW::WIDTH, WINDOW::HEIGHT);
}

void Quadtree::render(Quad* root) {
	root->rect.renderOutline(255, 0, 0);

	for (int i = 0; i < root->children.size(); i++) {
		render(&root->children[i]);
	}
}

void Quadtree::update(Quad* root) {
	for (auto it = root->people.begin(); it != root->people.end(); it++) {
		it.value().update();
	}
}

Quad* Quadtree::search(int x, int y, Quad* root) {
	if (!root->rect.CollidePoint(x, y)) {
		std::string tmp = "Out of range: ";
		std::stringstream buffer; buffer << x;
		tmp += buffer.str() + " ";
		buffer.str("");
		buffer << y;
		tmp += buffer.str() + "  SDL_Rect {";
		buffer.str("");
		buffer << root->rect.dest.x;
		tmp += buffer.str() + ", ";
		buffer.str("");
		buffer << root->rect.dest.y;
		tmp += buffer.str() + ", ";
		buffer.str("");
		buffer << root->rect.dest.w;
		tmp += buffer.str() + ", ";
		buffer.str("");
		buffer << root->rect.dest.h;
		tmp += buffer.str() + "}";
		buffer.str("");
		throw std::exception(tmp.c_str());
	}


	for (int i = 0; i < root->children.size(); i++) {
		return search(x, y, &root->children[i]);
;	}

	return root;
}