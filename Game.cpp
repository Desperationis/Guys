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


#include "Game.h"
#include "Tools/TM.h"
#include "Tools/Font.h"
#include "Tools/Timer.h"
#include "Tools/InputSystem.h"
#include "Tools/Rect.h"
#include "Tools/DebugTools.h"
#include "Tools/Menu/Overlay/Overlay.h"
#include "Quadtree.h"
#include "Setup.h"

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
bool vsync = WINDOW::VSYNC;
void Game::update() {
	if (vsync != WINDOW::VSYNC) {
		vsync = WINDOW::VSYNC;
		SDL_DestroyRenderer(TM::renderer);
		TM::rendererInit(Game::window);
		overlay->init();
	}

	frame++;
	if (FOOD::GROWTH == 0) {
		FOOD::GROWTH = 1;
	}
	if (frame % FOOD::GROWTH == 0) {
		for (int i = 0; i < FOOD::MULTIPLIER; i++) {
			int x = (rand() % (WINDOW::WIDTH - 4)) + 2;
			int y = (rand() % (WINDOW::HEIGHT - 4)) + 2;
			Entity e(x, y);
			e.plant = true;
			quadtree->insert(e);
		}
	}

	if (WINDOW::FPS_COUNTER) {
		if (fpsTimer->getTicks() > 10000) {
			//refreshes frame rate counter
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
	
	while(SDL_PollEvent(&event)) {
		if(event.type == SDL_QUIT) {
			running = false;
		}

		if (InputSystem::keys[SDL_SCANCODE_ESCAPE]) {
			running = false;
		}
	}
}

bool Game::isRunning() const {
	return running;
}
