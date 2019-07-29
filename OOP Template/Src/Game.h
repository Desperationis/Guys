#pragma once
#include "includes.h"

class Timer;
class Game {
public:
	Game(const char* name, int xpos, int ypos, int width, int height, Uint32 flags);
	void update();
	void render();
	void events();
	bool isRunning() const;
private:
	SDL_Event event;
	Timer* fpsTimer;
	int countedFrames = 0;
	bool running = false;
	bool counter = false;
	SDL_Window* window;
};
