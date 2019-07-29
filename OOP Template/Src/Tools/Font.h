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

private:
	TTF_Font* font;
	const char* loadedFile;
	RENDER_TYPE renderType = _NULL_;
	SDL_Color fontColor;
	SDL_Color shadeColor;
	SDL_Rect ref;
	int pt;
};