#include "Font.h"
#include "../includes.h"
#include "TM.h"

Font::Font(const char* file, int pt_) {
	font = TTF_OpenFont(file, pt_);
	if (font == NULL) {
		std::cout << "TTF_OpenFont: " << TTF_GetError() << std::endl;
		system("pause");
	}
	loadedFile = file;
	pt = pt_;
	fontColor = SDL_Color{ 0,0,0,255 };
	shadeColor = SDL_Color{ 255,255,255,255 };
}

Font::Font(const char* file, int pt_, SDL_Color& color) {
	font = TTF_OpenFont(file, pt_);
	loadedFile = file;
	pt = pt_;
	fontColor = color;
	shadeColor = SDL_Color{ 255,255,255,255 };
}

Font::~Font() {
	TTF_CloseFont(font);
}

const char* Font::getFile() const {
	return loadedFile;
}

void Font::loadFile(const char* file) {
	TTF_CloseFont(font);
	font = TTF_OpenFont(file, pt);
	loadedFile = file;
}

void Font::loadColor(SDL_Color& fontColor_) {
	fontColor = fontColor_;
}

void Font::loadColor(int r, int g, int b, int a) {
	fontColor.r = r;
	fontColor.g = g;
	fontColor.b = b;
	fontColor.a = a;
}

void Font::loadShadeColor(SDL_Color& shadeColor_) {
	shadeColor = shadeColor_;
}

void Font::loadShadeColor(int r, int g, int b, int a) {
	shadeColor.r = r;
	shadeColor.g = g;
	shadeColor.b = b;
	shadeColor.a = a;
}

void Font::loadSize(int pt_) {
	TTF_CloseFont(font);
	font = TTF_OpenFont(loadedFile, pt_);
	pt = pt_;
}

void Font::loadRenderType(RENDER_TYPE type) {
	renderType = type;
}

void Font::setDest(SDL_Rect& dest) {
	dest.w = ref.w;
	dest.h = ref.h;
}


SDL_Texture* Font::toText(const char* text) {
	SDL_Surface* tmp = TTF_RenderText_Solid(font, text, fontColor);

	switch (renderType) {
	case SOLID:
		tmp = TTF_RenderText_Solid(font, text, fontColor);
		break;
	case SHADED:
		tmp = TTF_RenderText_Shaded(font, text, fontColor, shadeColor);
		break;
	case BLENDED:
		tmp = TTF_RenderText_Blended(font, text, fontColor);
		break;
	case _NULL_:
		std::cout << "Render Type not set for " << loadedFile << std::endl;
		break;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(TM::renderer, tmp);
	SDL_QueryTexture(texture, NULL, NULL, &ref.w, &ref.h);
	SDL_FreeSurface(tmp);
	tmp = nullptr;
	return texture;
}