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
	tsl::hopscotch_map<Uint64, Entity> entities;
};

struct Quadtree {
	Quadtree();

	enum ENTITIES { FOOD, HOOMAN };

	std::vector<Entity> tmp;
	std::vector<Entity> queue;

	void clearQueue();
	void clear(Quad* root);
	void erase(Entity& entity);
	void render(Quad* root);
	void update(Quad* root);
	void insert(Entity& entity);
	Quad* search(int& x, int& y, Quad* root);
	Quad* root;
};
