#include "Game.h"
#include "Tools/TM.h"
#include "Tools/Font.h"
#include "Tools/Timer.h"
#include "Tools/InputSystem.h"
#include "Tools/Rect.h"
#include "Food.h"
#include "Quadtree.h"

std::vector<Food> foods;
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
}

bool clicked = false;
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

	if (!clicked && InputSystem::mouse[InputSystem::MOUSE::LEFT]) {
		foods.push_back(Food());
		foods.back().rect->dest.x = InputSystem::mouse[InputSystem::MOUSE::X];
		foods.back().rect->dest.y = InputSystem::mouse[InputSystem::MOUSE::Y];
		foods.back().rect->update();
	}
	clicked = InputSystem::mouse[InputSystem::MOUSE::LEFT];
}

void Game::render() {
	TM::renderClear();

	for (int i = 0; i < foods.size(); i++) {
		foods[i].render();
	}

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