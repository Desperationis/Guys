#pragma once
#include "Tools/TM.h"
#include "Tools/InputSystem.h"
#include "includes.h"

struct Button;
struct Overlay {
	Overlay();
	void update();
	void render();

	SDL_Rect dest;
	bool visible = false, toggle;
	std::vector<Button> buttons;
};
