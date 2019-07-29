#include "Timer.h"


Timer::Timer() {
	startTicks = 0;
	pausedTicks = 0;

	paused = false;
	started = false;
}

void Timer::start() {
	started = true;
	paused = false;

	startTicks = SDL_GetTicks();
	pausedTicks = 0;
}

void Timer::stop() {
	startTicks = 0;
	pausedTicks = 0;

	paused = false;
	started = false;
}

void Timer::pause() {
	if (started && !paused) {
		paused = true;
		pausedTicks += SDL_GetTicks() - startTicks;
		startTicks = 0;
	}
}

void Timer::unpause() {
	if (started && paused) {
		paused = false;
		startTicks = SDL_GetTicks() - pausedTicks;
		pausedTicks = 0;
	}
}

Uint32 Timer::getTicks() {
	Uint32 time = 0;

	if (started) {
		if (paused) {
			// return paused ticks
			time = pausedTicks;
		}
		else {
			// return relative time
			time = SDL_GetTicks() - startTicks;
		}
	}

	return time;
}

bool Timer::isStarted() const {
	return started;
}

bool Timer::isPaused() const {
	return paused;
}