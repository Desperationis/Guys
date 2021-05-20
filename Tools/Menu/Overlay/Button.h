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
#include "../../../includes.h"
#include "../../Font.h"
#include "../../Rect.h"

struct Button {
	Button() {};
	virtual void update() {};
	virtual void render() {};
	virtual void clean() {};
	virtual void addButton(Button* button) { std::cout << "Wrong derived class" << std::endl; };

	SDL_Rect textDest;
	Rect rect;
	SDL_Texture* text;
	SDL_Color color{ 255,255,255, 240 };
	bool pressed = false;
	bool preview = false;
};
