#pragma once
#include "SDL.h"
#include <fstream>
#include <iostream>

class InputSystem
{
public:
	InputSystem();

	// brief Pumps Events to be queried.
	static void PumpEvents();

	// returns the value of one of the controller's buttons
	static Sint16 GetButton(const SDL_GameControllerButton button);

	// returns the value of one of the controller's axes
	static Sint16 GetAxis(const SDL_GameControllerAxis axis);



	enum MOUSE { X, Y, LEFT, RIGHT };
	static SDL_GameController* controller;
	static int mouse[4];
	static bool controllerConnected, usingController;
	static const Uint8* keys;
};
