#include "Game.h"
#include "Tools/TM.h"
#include "Tools/Font.h"
#include "Tools/Timer.h"
#include "Tools/InputSystem.h"
#include "Tools/Rect.h"
#include "Quadtree.h"

Quadtree* quadtree;

Game::Game(const char* name, int xpos, int ypos, int width, int height, Uint32 flags) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL failed to Initalize");
		system("pause");
	}

	if(TTF_Init() != 0) {
		printf("SDL_TTF failed to Initalize");
		system("pause");
	}

	window = SDL_CreateWindow(name, xpos, ypos, width, height, flags);
	TM::rendererInit(window);
	TM::renderDrawColor(255,255,255);
	running = true;
	fpsTimer = new Timer();
	fpsTimer->start();
	SDL_PollEvent(&event);

	quadtree = new Quadtree();

	for (unsigned int i = 0; i < 1000; i++) {
		int x = rand() % 801;
		int y = rand() % 801;
		quadtree->insert(x, y, quadtree->root, quadtree->HOOMAN);
	}
	for (unsigned int i = 0; i < 40; i++) {
		int x = rand() % 801;
		int y = rand() % 801;
		quadtree->insert(x, y, quadtree->root, quadtree->FOOD);
	}
}

bool Lclicked = false;
bool Rclicked = false;
bool Lshift = false;
std::vector<Entity> tmp;
void Game::update() {
	//refreshes frame rate counter
	if (counter) {
		if (fpsTimer->getTicks() > 10000) {
			fpsTimer->stop();
			fpsTimer->start();
			countedFrames = 0;
		}
		float avgFPS = countedFrames / (fpsTimer->getTicks() / 1000.0f);
		if (avgFPS > 2000000) {
			avgFPS = 0;
		}
		std::cout << avgFPS << std::endl;
	}

	// Debug Tools
	int x = InputSystem::mouse[InputSystem::MOUSE::X];
	int y = InputSystem::mouse[InputSystem::MOUSE::Y];
	char type = '-';
	if (InputSystem::mouse[InputSystem::MOUSE::LEFT] && !Lclicked) 
		quadtree->insert(x, y, quadtree->root, Quadtree::FOOD);
	if (InputSystem::mouse[InputSystem::MOUSE::RIGHT] && !Rclicked) 
		quadtree->insert(x, y, quadtree->root, Quadtree::HOOMAN);
	Lclicked = InputSystem::mouse[InputSystem::MOUSE::LEFT];
	Rclicked = InputSystem::mouse[InputSystem::MOUSE::RIGHT];

	if (InputSystem::keys[SDL_SCANCODE_LSHIFT] && Lshift) {
		std::cout << "Input X: ", std::cin >> x, std::cout << "\n";
		std::cout << "Input y: ", std::cin >> y, std::cout << "\n";
		do {
			std::cout << "Type [F / H]: ", std::cin >> type, std::cout << "\n";
			switch (type) {
			case 'H':
				quadtree->insert(x, y, quadtree->root, Quadtree::HOOMAN);
				break;
			case 'F':
				quadtree->insert(x, y, quadtree->root, Quadtree::FOOD);
				break;
			default:
				std::cout << "Didn't quite catch that.\n" << std::endl;
				break;
			}
		} while (type != 'F' && type != 'H');
	}
	Lshift = InputSystem::keys[SDL_SCANCODE_LSHIFT];

	if (InputSystem::keys[SDL_SCANCODE_GRAVE]) {
		quadtree->clear(quadtree->root);
	}

	// Debug Tools

	quadtree->update(quadtree->root);

	for (unsigned int i = 0; i < quadtree->queue.size(); i++) {
		tmp.push_back(*quadtree->queue[i]);
		quadtree->erase(quadtree->queue[i]);
	}
	for (unsigned int i = 0; i < tmp.size(); i++) {
		if (quadtree->root->rect.CollidePoint(tmp[i].rect.dest.x, tmp[i].rect.dest.y)) {
			quadtree->insert(tmp[i].rect.dest.x, tmp[i].rect.dest.y, quadtree->root, quadtree->HOOMAN, tmp[i].dead);
		} 
		tmp[i].clean();
	}

	quadtree->queue.clear();
	tmp.clear();
}

void Game::render() {
	TM::renderClear();

	quadtree->render(quadtree->root);

	TM::renderDrawColor(255, 255, 255);
	TM::renderPresent();
	countedFrames++;
}

bool TAB_PRESSED = false;
void Game::events() {
	SDL_PollEvent(&event);
	InputSystem::PumpEvents();

	switch (event.window.event) {
	case SDL_WINDOWEVENT_CLOSE:
		running = false;
	}

	if (InputSystem::keys[SDL_SCANCODE_ESCAPE]) {
		running = false;
	}

	if (InputSystem::keys[SDL_SCANCODE_TAB] && !TAB_PRESSED) {
		counter = !counter;
	}
	TAB_PRESSED = InputSystem::keys[SDL_SCANCODE_TAB];
}

bool Game::isRunning() const {
	return running;
}