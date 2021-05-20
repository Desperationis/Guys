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
#include "SDL_ttf.h"

class Font {
public:
	// Data class that handles fonts, colors, sizes, ect.
	enum RENDER_TYPE { SOLID, SHADED, BLENDED, _NULL_ };

	Font(const char* file, int pt_);
	Font(const char* file, int pt_, SDL_Color& color);
	~Font();

	const char* getFile() const;

	void loadFile(const char* file);
	void loadColor(SDL_Color& fontColor_);
	void loadShadeColor(SDL_Color& shadeColor_);
	void loadShadeColor(int r, int g, int b, int a);
	void loadColor(int r, int g, int b, int a);
	void loadSize(int pt_);
	void loadRenderType(RENDER_TYPE type);
	void setDest(SDL_Rect& dest);
	SDL_Texture* toText(const char* text);
	TTF_Font* font;

private:
	const char* loadedFile;
	RENDER_TYPE renderType = _NULL_;
	SDL_Color fontColor;
	SDL_Color shadeColor;
	SDL_Rect ref;
	int pt;
};
