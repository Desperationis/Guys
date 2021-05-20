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
