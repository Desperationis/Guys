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