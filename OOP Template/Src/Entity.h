#pragma once
#include "SDL.h"
#include "includes.h"
#include "Tools/Rect.h"

struct Quad;
struct Entity {
	Entity() {};
	Entity(int x, int y);
	bool update();
	void render();
	void clean();
	void copy(Entity& entity);

	static Uint64 counter;
	Uint64 id = -1;
	Rect rect, eyes;
	Quad* parent = nullptr;
	SDL_Color color;
	bool plant = false;


	bool dead = false;
	bool relocate = false;
	bool roam = false;

	float energy = 1000.0f;
	float speed = 2.0f;
	float sight = 0.0f;
	float angle = 0.0f;
private:
	std::vector<Quad*> searches;
	Entity* closest = nullptr;


	void search(Quad* root);

	void makeBabbe();
	bool look(); // looks for food

};