#pragma once
#include "SDL.h"
#include "SDL_image.h"

class Font;
struct TM
{
	// TM - Texture Manager
	// Holds the renderer for the window so it can easily handle textures and the renderer.


	static SDL_Renderer* renderer;

	// renderer
	static void rendererInit(SDL_Window* window);
	static void renderClear();
	static void renderPresent();
	static void renderDrawColor(int r, int g, int b, int a = 255);
	static void renderDrawColor(SDL_Color& color);

	// basic rendering
	static void DrawTexture(SDL_Texture*& texture, SDL_Rect & dest, SDL_Rect& scr);
	static void DrawTexture(SDL_Texture*& texture, SDL_Rect & dest);
	static void DrawTexture(SDL_Texture*& texture);

	// complex rendering
	static void DrawTextureEx(SDL_Texture*& texture, SDL_Rect& dest, SDL_Rect& scr, SDL_RendererFlip SDL_Flip,SDL_Point& p, double angle);
	static void DrawTextureEx(SDL_Texture*& texture, SDL_Rect& dest, SDL_Rect& scr, SDL_RendererFlip SDL_Flip, double angle);
	static void DrawTextureEx(SDL_Texture*& texture, SDL_Rect& dest, SDL_RendererFlip SDL_Flip, double angle);

	// basic loading
	static SDL_Texture* LoadTexture(const char* texture);
	static SDL_Texture* LoadBWTexture(const char* texture);

	// complex blending
	static void SetAlphaBlending(SDL_Texture*& texture);
	static void RemoveAlphaBlending(SDL_Texture*& texture);
	static void SetAlpha(SDL_Texture*& texture, Uint8 alpha);

	// complex altering
	static void SetColorMod(SDL_Texture*& texture, Uint8 R, Uint8 G, Uint8 B);
};