#include "Quadtree.h"
#include "Setup.h"
#include "Food.h"

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

void Quadtree::render(Quad* root) {
	root->rect.renderOutline(255, 0, 0);

	for (auto it = root->people.begin(); it != root->people.end(); it++) {
		it.value().render();
	}

	for (auto it = root->foods.begin(); it != root->foods.end(); it++) {
		it.value().render();
	}

	for (int i = 0; i < root->children.size(); i++) {
		render(&root->children[i]);
	}
}

void Quadtree::update(Quad* root) {
	for (auto it = root->people.begin(); it != root->people.end(); it++) {
		if (it.value().update()) {
			queue.push_back(&it.value());
		}
	}

	for (int i = 0; i < root->children.size(); i++) {
		update(&root->children[i]);
	}
}

void Quadtree::insert(int& x, int& y, Quad* root, ENTITIES e, bool dead) {
	Quad* quad = nullptr;
	try {
		quad = search(x, y, root);
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		system("pause");
		return;
	}
	SDL_Rect& dest = quad->rect.dest;

	switch (e) {
	case FOOD:
		quad->foods[Food::counter] = Food(x, y);
		quad->foods[Food::counter].parent = quad;
		Food::counter++;
		break;
	case HOOMAN:
		SDL_Color c{ 255,0,0,255 };
		quad->people[Hooman::counter] = Hooman(x, y, c);
		quad->people[Hooman::counter].parent = quad;
		Hooman::counter++;
		break;
	}

	if (quad->foods.size() + quad->people.size() >= 4) {
		if (quad->children.size() == 0) {
			quad->children.push_back(Quad(dest.x, dest.y, dest.w / 2, dest.h / 2));
			quad->children.push_back(Quad(dest.x + (dest.w / 2), dest.y, dest.w / 2, dest.h / 2));
			quad->children.push_back(Quad(dest.x, dest.y + (dest.h / 2), dest.w / 2, dest.h / 2));
			quad->children.push_back(Quad(dest.x + (dest.w / 2), dest.y + (dest.h / 2), dest.w / 2, dest.h / 2));
		}

		for (unsigned int i = 0; i < quad->children.size(); i++) {
			quad->children[i].parent = quad;
		}

		for (auto it = quad->foods.begin(); it != quad->foods.end(); it++) {
			for (unsigned int i = 0; i < quad->children.size(); i++) {
				//change to collide rect for higher accuracy over performance
				if (quad->children[i].rect.CollidePoint(it.value().rect->dest.x, it.value().rect->dest.y)) {
					insert(it.value().rect->dest.x, it.value().rect->dest.y, &quad->children[i], FOOD, it.value().dead);
					it.value().clean();
					break;
				}

			}
		}
		for (auto it = quad->people.begin(); it != quad->people.end(); it++) {
			for (unsigned int i = 0; i < quad->children.size(); i++) {
				//change to collide rect for higher accuracy over performance
				if (quad->children[i].rect.CollidePoint(it.value().rect->dest.x, it.value().rect->dest.y)) {
					insert(it.value().rect->dest.x, it.value().rect->dest.y, &quad->children[i], HOOMAN, it.value().dead);
					it.value().clean();
					break;
				}

			}
		}
		quad->foods.clear();
		quad->people.clear();
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
		throw std::exception(tmp.c_str());
		return root;
	}


	for (int i = 0; i < root->children.size(); i++) {
		if (root->children[i].rect.CollidePoint(x, y)) {
			return search(x, y, &root->children[i]);
		}
;	}

	return root;
}

void Quadtree::erase(Food* food) {
	Quad* quad = nullptr;
	try {
		 quad = search(food->rect->dest.x, food->rect->dest.y, food->parent);
	}
	catch (std::exception& e) {
		food->parent->foods.erase(food->id);
	}

	quad->foods.erase(food->id);
	food = nullptr;

	int sum = 0;
	for (unsigned int i = 0; i < quad->parent->children.size(); i++) {
		sum += quad->parent->children[i].foods.size();
	}

	if (sum < 4) {
		for (unsigned int i = 0; i < quad->parent->children.size(); i++) {
			for (auto it = quad->parent->children[i].foods.begin(); it != quad->parent->children[i].foods.end(); it++) {
				quad->parent->foods[it.key()] = it.value();
				quad->parent->foods[it.key()].parent = quad;
			}
		}
		quad->parent->children.clear();
	}
	quad = nullptr;
}

void Quadtree::erase(Hooman* human) {
	Quad* quad = nullptr;
	try {
		quad = search(human->rect->dest.x, human->rect->dest.y, human->parent);
	}
	catch (std::exception& e) {
		human->parent->people.erase(human->id);
		return;
	}
	quad->people.erase(human->id);
	human = nullptr;
	
	/*int sum = 0;
	for (unsigned int i = 0; i < quad->parent->children.size(); i++) {
		sum += quad->parent->children[i].people.size();
	}

	if (sum < 4) {
		for (unsigned int i = 0; i < quad->parent->children.size(); i++) {
			for (auto it = quad->parent->children[i].people.begin(); it != quad->parent->children[i].people.end(); it++) {
				quad->parent->people[it.key()] = it.value();
				quad->parent->people[it.key()].parent = quad;
			}
		}
		quad->parent->children.clear();
	}
	quad = nullptr;*/
}