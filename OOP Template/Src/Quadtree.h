#pragma once
#include "includes.h"

#include "Food.h" // just for proof-of-concept

struct Quad {
	Quad(int x, int y, int w, int h);
	SDL_Rect boundaries;
	Quad* parent = nullptr;
	std::vector<Quad*> quads;
	tsl::hopscotch_map<Uint32, Food**> data; // will only be stored in the lowest child quad
};

struct Quadtree {
	Quadtree();
	void insert(Food* food);
	const Quad* render(const Quad* startingQuad) const;
	Quad* search(const Food& food, Quad* startingQuad) const;
	bool valid(const Food& food, const Quad* quad) const;

	Quad* root;
};

