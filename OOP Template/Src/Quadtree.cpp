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
		if (!tmp[i].plant) {
			if (root->rect.CollidePoint(tmp[i].rect.center[0], tmp[i].rect.center[1])) {
				insert(tmp[i]);
			}
		}
		erase(tmp[i]);
	}

	tmp.clear();

	for (int i = 0; i < queue.size(); i++) {
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
		std::cout << e.what() << std::endl;
		//system("pause");
		return;
	}
	SDL_Rect& dest = quad->rect.dest;

	quad->entities[Entity::counter] = Entity(entity.rect.dest.x, entity.rect.dest.y);
	quad->entities[Entity::counter].copy(entity);


	quad->entities[Entity::counter].parent = quad;
	Entity::counter++;

	if (quad->iteration > QUADTREE::MAX_ITERATION) {
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
		throw std::exception(tmp.c_str());
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