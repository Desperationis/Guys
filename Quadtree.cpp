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


#include "Quadtree.h"
#include "Setup.h"

Quad::Quad(int x, int y, int w, int h) {
	rect.dest.x = x;
	rect.dest.y = y;
	rect.dest.w = w;
	rect.dest.h = h;
	rect.update();
	parent = nullptr;
}

Quad::~Quad() {
	parent = nullptr;
}

Quadtree::Quadtree() {
	root = new Quad(0, 0, WINDOW::WIDTH, WINDOW::HEIGHT);
}

void Quadtree::clearQueue() {
	for (unsigned int i = 0; i < tmp.size(); i++) {
		if (tmp[i].relocate) {
			if (root->rect.CollidePoint(tmp[i].rect.center[0], tmp[i].rect.center[1])) {
				insert(tmp[i]);
			}
		}
		if (tmp[i].relocate || tmp[i].dead) {
			erase(tmp[i]);
		}
	}

	tmp.clear();

	for (unsigned int i = 0; i < queue.size(); i++) {
		insert(queue[i]);
	}
	queue.clear();
}

void Quadtree::render(Quad* root) {
	if (QUADTREE::RENDER) {
		root->rect.renderOutline(255, 0, 0);
	}

	for (auto it = root->entities.begin(); it != root->entities.end(); it++) {
		it.value().render();
	}

	for (unsigned int i = 0; i < root->children.size(); i++) {
		render(&root->children[i]);
	}
}

void Quadtree::update(Quad* root) {
	if (root->iteration > QUADTREE::MAX_ITERATION) {
		for (unsigned int i = 0; i < root->parent->children.size(); i++) {
			for (auto it = root->parent->children[i].entities.begin(); it != root->parent->children[i].entities.end(); it++) {
				root->parent->entities[it.key()] = it.value();
				root->parent->entities[it.key()].parent = root->parent;
				it.value().clean();
			}
		}
		root->parent->children.clear();
		root = nullptr;
		return;
	}


	// ERASING CODE HERE
	bool flag = true;
	if (root->children.size() != 0) {
		for (unsigned int i = 0; i < root->children.size(); i++) {
			if (root->children[i].children.size() != 0) {
				flag = false;
				break;
			}
		}
	}

	//if I have children
		//check if they are lowest subdivision
		//if they are, flag = true;


	if (flag) {
		// only run if at lowest subdivision
		int sum = 0;

		for (unsigned int i = 0; i < root->children.size(); i++) {
			sum += root->children[i].entities.size();
		}

		if (sum < 4) {
			// move data up from children
			for (unsigned int i = 0; i < root->children.size(); i++) {
				for (auto it = root->children[i].entities.begin(); it != root->children[i].entities.end(); it++) {
					root->entities[it.key()] = it.value();
					root->entities[it.key()].parent = root;
					it.value().clean();
				}
			}
			root->children.clear();
		}
	}

	// ERASING CODE HERE

	for (auto it = root->entities.begin(); it != root->entities.end(); it++) {
		if (it.value().update()) {
			tmp.push_back(it.value());
		}
	}

	for (unsigned int i = 0; i < root->children.size(); i++) {
		update(&root->children[i]);
	}

	clearQueue();
}

void Quadtree::insert(Entity& entity) {
	Quad* quad = nullptr;
	try {
		quad = search(entity.rect.center[0], entity.rect.center[1], root);
	}
	catch (std::exception& e) {
		if (DEBUG::OUT_OF_BOUNDS) {
			std::cout << e.what() << std::endl;
		}
		return;
	}
	SDL_Rect& dest = quad->rect.dest;

	quad->entities[Entity::counter] = Entity(entity.rect.dest.x, entity.rect.dest.y);
	if (!entity.plant) {
		entity.rect.dest.w = HOOMAN::SIZE;
		entity.rect.dest.h = HOOMAN::SIZE;
		entity.rect.update();
	}
	quad->entities[Entity::counter].copy(entity);


	quad->entities[Entity::counter].parent = quad;
	Entity::counter++;

	if (quad->iteration == QUADTREE::MAX_ITERATION) {
		// do not make any more quads at this point
		quad = nullptr;
		return;
	}

	if (quad->entities.size() >= 4) {
		if (quad->children.size() == 0) {
			quad->children.push_back(Quad(dest.x, dest.y, dest.w / 2, dest.h / 2));
			quad->children.push_back(Quad(dest.x + (dest.w / 2), dest.y, dest.w / 2, dest.h / 2));
			quad->children.push_back(Quad(dest.x, dest.y + (dest.h / 2), dest.w / 2, dest.h / 2));
			quad->children.push_back(Quad(dest.x + (dest.w / 2), dest.y + (dest.h / 2), dest.w / 2, dest.h / 2));
		}

		for (unsigned int i = 0; i < quad->children.size(); i++) {
			quad->children[i].parent = quad;
			quad->children[i].iteration = quad->iteration + 1;
		}

		for (auto it = quad->entities.begin(); it != quad->entities.end(); it++) {
			for (unsigned int i = 0; i < quad->children.size(); i++) {
				//change to collide rect for higher accuracy over performance
				if (quad->children[i].rect.CollidePoint(it.value().rect.center[0], it.value().rect.center[1])) {
					if (it.value().plant) {
						insert(it.value());
					}
					else {
						insert(it.value());
					}
					it.value().clean();
					break;
				}

			}
		}
		quad->entities.clear();
	}
	quad = nullptr;
}

Quad* Quadtree::search(int& x, int& y, Quad* root) {
	if (!root->rect.CollidePoint(x, y)) {
		std::string tmp = "Out of range: ";
		std::stringstream buffer; buffer << x;
		tmp += buffer.str() + " ";
		buffer.str("");
		buffer << y;
		tmp += buffer.str() + "  SDL_Rect {";
		buffer.str("");
		buffer << root->rect.dest.x;
		tmp += buffer.str() + ", ";
		buffer.str("");
		buffer << root->rect.dest.y;
		tmp += buffer.str() + ", ";
		buffer.str("");
		buffer << root->rect.dest.w;
		tmp += buffer.str() + ", ";
		buffer.str("");
		buffer << root->rect.dest.h;
		tmp += buffer.str() + "}";
		buffer.str("");
		throw std::runtime_error(tmp.c_str());
		return root;
	}

	for (unsigned int i = 0; i < root->children.size(); i++) {
		if (root->children[i].rect.CollidePoint(x, y)) {
			return search(x, y, &root->children[i]);
		}
;	}

	return root;
}

void Quadtree::erase(Entity& entity) {
	Quad* quad = entity.parent;
	entity.clean();
	quad->entities.erase(entity.id);
	quad = nullptr;
}

void Quadtree::clear(Quad* quad) {

	//if lowest, delete children
	//assign each quad->parent to nullptr

	if (quad->entities.size() != 0) {
		for (auto it = quad->entities.begin(); it != quad->entities.end(); it++) {
			it.value().clean();
		}
		quad->entities.clear();
	}

	for (unsigned int i = 0; i < quad->children.size(); i++) {
		clear(&quad->children[i]);
	}
	quad->children.clear();

	quad->parent = nullptr;
}
