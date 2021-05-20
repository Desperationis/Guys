// Simulation of life written in C++ and SDL. 
// Copyright (C) 2021 Diego Contreras
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.


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
