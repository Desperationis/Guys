#pragma once
#include "SDL.h"

class Timer {
public:
	Timer();

	// basic timer controls
	void start();
	void stop();
	void pause();
	void unpause();

	// get timer time
	Uint32 getTicks();

	// returns values

	bool isStarted() const;
	bool isPaused() const;
private:
	// the clock time when the timer is started
	Uint32 startTicks;

	// the ticks stored when the timer is paused
	Uint32 pausedTicks;

	// status
	bool paused;
	bool started;
};