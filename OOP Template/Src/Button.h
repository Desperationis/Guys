#pragma once
#include "SDL.h"
#include "includes.h"
#include "Tools/Font.h"
#include "Tools/Rect.h"

struct Button {
	Button() {};
	virtual void update() {};
	virtual void render() {};
	virtual void addButton(Button* button) { std::cout << "Wrong derived class" << std::endl; };

	SDL_Rect textDest;
	Rect rect;
	SDL_Texture* text;
	SDL_Color color{ 255,255,255, 240 };
	bool pressed = false;
	bool preview = false;
};