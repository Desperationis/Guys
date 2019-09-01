#pragma once
#include "Overlay/Button.h"


struct Dropdown : public Button{
	Dropdown(const char* text, int x, int y, int w, int h);
	void update() override;
	void render() override;
	void addButton(Button* button) override;


	static Font* font;
	std::vector<Button*> dropDown;
};
