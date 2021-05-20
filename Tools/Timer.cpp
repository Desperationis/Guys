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
