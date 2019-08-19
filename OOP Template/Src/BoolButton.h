#pragma once
#include "SDL.h"
#include "includes.h"
#include "Tools/Font.h"
#include "Tools/Rect.h"
#include "Button.h"

struct BoolButton : public Button {
	BoolButton(const char* text, int x, int y, int w, int h, bool& value) ;
	void update() override;
	void render() override;

	
	static Font* font;
	bool* value;
};
