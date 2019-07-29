#pragma once
#include "Tools/Rect.h"
#include "includes.h"

struct Food;
struct Quad {
	Quad(int x, int y, int w, int h);

	Quad* parent;
	Rect rect;
	std::vector<Quad> children;
	tsl::hopscotch_map<Uint32, Food**> data;
};

struct Quadtree {
	Quadtree();

	void insert();
	void search();
	void render(Quad* root);
	Quad* root;
};