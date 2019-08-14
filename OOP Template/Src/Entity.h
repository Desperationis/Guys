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

	static Uint32 counter;
	bool dead = false;
	Uint32 id = -1;
	Rect rect, eyes;
	Quad* parent = nullptr;
	SDL_Color color;
	bool plant = false;


	float energy = 300.0f;
	float speed = 2.0f;
private:
	std::vector<Quad*> searches;
	Entity* closest = nullptr;


	bool look();
	void search(Quad* root);

};