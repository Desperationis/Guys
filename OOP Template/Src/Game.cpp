#include "Game.h"
#include "Tools/TM.h"
#include "Tools/Font.h"
#include "Tools/Timer.h"
#include "Tools/InputSystem.h"
#include "Tools/Rect.h"
#include "Quadtree.h"
#include "Tools/DebugTools.h"
#include "Setup.h"
#include "Overlay.h"

Quadtree* Game::quadtree;
Overlay* overlay;

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
	debugTools = new DebugTools();
	overlay = new Overlay();

	for (int i = 0; i < HOOMAN::BEGIN; i++) {
		int x = (rand() % (WINDOW::WIDTH - 4)) + 2;
		int y = (rand() % (WINDOW::HEIGHT - 4)) + 2;
		Entity e(x, y);
		quadtree->insert(e);
	}
	for (int i = 0; i < FOOD::BEGIN; i++) {
		int x = (rand() % (WINDOW::WIDTH - 4)) + 2;
		int y = (rand() % (WINDOW::HEIGHT - 4)) + 2;
		Entity e(x, y);
		e.plant = true;
		quadtree->insert(e);
	}
}

Uint32 frame = 0; // frame counter

void Game::update() {
	frame++;
	if (frame % FOOD::GROWTH == 0) {
		for (int i = 0; i < FOOD::MULTIPLIER; i++) {
			int x = (rand() % (WINDOW::WIDTH - 4)) + 2;
			int y = (rand() % (WINDOW::HEIGHT - 4)) + 2;
			Entity e(x, y);
			e.plant = true;
			quadtree->insert(e);
		}
	}

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

	
	debugTools->update();

	overlay->update();
	quadtree->update(quadtree->root);
}

void Game::render() {
	TM::renderClear();

	quadtree->render(quadtree->root);
	overlay->render();

	TM::renderDrawColor(255, 255, 255);
	TM::renderPresent();
	countedFrames++;
}

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

	if (WINDOW::FPS_COUNTER) {
		counter = !counter;
		WINDOW::FPS_COUNTER = false;
	}
}

bool Game::isRunning() const {
	return running;
}