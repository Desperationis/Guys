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
#include "Button.h"

struct BoolButton : public Button {
	BoolButton(const char* text, int x, int y, int w, int h, bool& value, bool indicatorHidden_ = false) ;
	void update() override;
	void render() override;
	void clean() override;
	void renderValue();

	
	static Font* font;
	static Font* indicatorFont;
	bool* value;
	int loaded = -1;

	bool indicatorBool = false;
	bool indicatorHidden = false;
	SDL_Texture* indicator = nullptr;
	SDL_Rect indicatorRect;
};
