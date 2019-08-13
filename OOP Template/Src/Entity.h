#pragma once
#include "SDL.h"
#include "includes.h"
#include "Tools/Rect.h"

struct Quad;
struct Entity {
	Entity() { 
		id = -1; 
	};
	Entity(int x, int y, SDL_Color _color = { 0,0,0,255 });
	bool update();
	void render();
	void clean();
	void look();
	void search(Quad* root);

	static Uint32 counter;
	bool dead = false;
	Uint32 id = -1;
	Rect rect, eyes;
	Quad* parent = nullptr;
	Entity* closest = nullptr;
	SDL_Color color;
	std::vector<Quad*> searches;

	std::vector<Entity*> chasingMe;
	bool plant = false;
};