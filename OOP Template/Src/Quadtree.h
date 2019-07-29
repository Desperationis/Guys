#pragma once
#include "Tools/Rect.h"
#include "includes.h"
#include "Food.h"

struct Quad {
	Quad(int x, int y, int w, int h);

	Quad* parent;
	Rect rect;
	std::vector<Quad> children;
	tsl::hopscotch_map<Uint32, Food> data;
};

struct Quadtree {
	Quadtree();

	void render(Quad* root);
	void insert(int x, int y, Quad* root);
	Quad& search(int x, int y, Quad& root);
	Quad* root;
};