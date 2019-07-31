#pragma once
#include "Tools/Rect.h"
#include "includes.h"
#include "Food.h"
#include "Hooman.h"

struct Quad {
	Quad(int x, int y, int w, int h);
	~Quad();

	Quad* parent;
	Rect rect;
	std::vector<Quad> children;
	tsl::hopscotch_map<Uint32, Food> foods;
	tsl::hopscotch_map<Uint32, Hooman> people;
};

struct Quadtree {
	Quadtree();

	enum ENTITIES { FOOD, HOOMAN };

	std::vector<Hooman*> queue;

	void erase(Food* food);
	void erase(Hooman* human);
	void render(Quad* root);
	void update(Quad* root);
	void insert(int& x, int& y, Quad* root, ENTITIES e, bool dead = false);
	Quad* search(int& x, int& y, Quad* root);
	Quad* root;
};