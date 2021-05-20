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


#include "InputSystem.h"

SDL_GameController* InputSystem::controller = nullptr;
bool InputSystem::controllerConnected = false;
bool InputSystem::usingController = false;
const Uint8* InputSystem::keys;
int InputSystem::mouse[4];

InputSystem::InputSystem() {
	for (int i = 0; i < SDL_NumJoysticks(); i++)
	{
		if (SDL_IsGameController(i))
		{
			controller = SDL_GameControllerOpen(i);
			if (controller)
			{
				SDL_GameControllerGetJoystick(controller);
				std::cout << "Joystick connected: " << SDL_GameControllerName(controller) << std::endl;

				controllerConnected = true;
				break;
			}
			else
			{
				std::cout << "Could not open Game Controller " << i << " " << std::endl;
			}
		}
	}
	SDL_GameControllerEventState(SDL_IGNORE);
	std::cout << "Keyboard connected." << std::endl;
}


void InputSystem::PumpEvents()
{
	SDL_PumpEvents();
	keys = SDL_GetKeyboardState(NULL);
	mouse[LEFT] = SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT);
	mouse[RIGHT] = SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT);
	SDL_GetMouseState(&mouse[X], &mouse[Y]);
}

Sint16 InputSystem::GetButton(const SDL_GameControllerButton button) {
	return SDL_GameControllerGetButton(controller, button);
}

Sint16 InputSystem::GetAxis(const SDL_GameControllerAxis axis) { 
	return SDL_GameControllerGetAxis(controller, axis); 
}
