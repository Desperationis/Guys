#pragma once
#include "../../TM.h"
#include "../../InputSystem.h"
#include "../../../includes.h"

struct Button;
struct Overlay {
	Overlay();
	void update();
	void render();
	void init();

	SDL_Rect dest;
	bool visible = false, toggle;
	std::vector<Button*> buttons;
};
