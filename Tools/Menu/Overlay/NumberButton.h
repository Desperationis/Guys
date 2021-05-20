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
#include "../../Timer.h"
#include "Button.h"

struct NumberButton : public Button {
	NumberButton(const char* text, int x, int y, int w, int h, int& value);
	void update() override;
	void render() override;
	void clean() override;
	void renderValue();


	SDL_Texture* currentValue = nullptr;
	SDL_Texture* left = nullptr;
	SDL_Texture* right = nullptr;
	SDL_Rect currentValueRect;
	Rect leftRect, rightRect;

	static Font* font;
	static Font* numberFont;
	static Timer fast;
	int* value;
	int pastValue = 0, loaded = 0;
};
