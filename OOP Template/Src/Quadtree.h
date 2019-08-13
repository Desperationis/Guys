#pragma once
#include "Tools/Rect.h"
#include "includes.h"
#include "Entity.h"

struct Quad {
	Quad(int x, int y, int w, int h);
	~Quad();

	int iteration = 0;
	Quad* parent;
	Rect rect;
	std::vector<Quad> children;
	tsl::hopscotch_map<Uint32, Entity> entities;
};

struct Quadtree {
	Quadtree();

	enum ENTITIES { FOOD, HOOMAN };

	std::vector<Entity*> queue;
	std::vector<Entity> tmp;

	void clearQueue();
	void clear(Quad* root);
	void erase(Entity* entity);
	void render(Quad* root);
	void update(Quad* root);
	void insert(Entity& entity);
	Quad* search(int& x, int& y, Quad* root);
	Quad* root;
};