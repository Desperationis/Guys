#pragma once
#include "TM.h"
#include "Font.h"

SDL_Renderer* TM::renderer = nullptr;

// renderer

void TM::rendererInit(SDL_Window* window) {
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}

void TM::renderClear() {
	SDL_RenderClear(renderer);
}

void TM::renderPresent() {
	SDL_RenderPresent(renderer);
}

void TM::renderDrawColor(int r, int g, int b, int a) {
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void TM::renderDrawColor(SDL_Color& color) {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}


// Basic Rendering Capabilities
void TM::DrawTexture(SDL_Texture*& texture, SDL_Rect& dest, SDL_Rect& scr){
	SDL_RenderCopy(renderer, texture, &scr, &dest);
}
void TM::DrawTexture(SDL_Texture*& texture, SDL_Rect& dest){
	SDL_RenderCopy(renderer, texture, NULL, &dest);
}
void TM::DrawTexture(SDL_Texture*& texture) { SDL_RenderCopy(renderer, texture, NULL, NULL); }

// Complex Rendering Capabilities

void TM::DrawTextureEx(SDL_Texture*& texture, SDL_Rect& dest, SDL_Rect& scr, SDL_RendererFlip SDL_Flip,SDL_Point& p,  double angle = 0.0)
{
	SDL_RenderCopyEx(renderer, texture, &scr, &dest, angle, &p, SDL_Flip);
}

void TM::DrawTextureEx(SDL_Texture*& texture, SDL_Rect& dest, SDL_Rect& scr, SDL_RendererFlip SDL_Flip, double angle = 0.0)
{
	SDL_RenderCopyEx(renderer, texture, &scr, &dest, angle, NULL, SDL_Flip);
}

void TM::DrawTextureEx(SDL_Texture*& texture, SDL_Rect& dest, SDL_RendererFlip SDL_Flip, double angle = 0.0)
{
	SDL_RenderCopyEx(renderer, texture, NULL, &dest, angle, NULL , SDL_Flip);
}



// Loading Capabilities

SDL_Texture* TM::LoadTexture(const char* texture)
{
	SDL_Surface* temp = IMG_Load(texture);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(temp);
	return tex;
}

SDL_Texture* TM::LoadBWTexture(const char* texture)
{
	SDL_Surface* tmp = IMG_Load(texture);
	if (tmp != NULL)
	{
		tmp = SDL_ConvertSurfaceFormat(tmp, SDL_PIXELFORMAT_ARGB8888, 0);
		SDL_Texture* tex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, tmp->w, tmp->h);


		Uint32 * pixels = static_cast<Uint32*>(tmp->pixels);
		for (int y = 0; y < tmp->h; y++)
		{
			for (int x = 0; x < tmp->w; x++)
			{
				Uint32 pixel = pixels[y * tmp->w + x];
				Uint8 r = pixel >> 16 & 0xFF;
				Uint8 g = pixel >> 8 & 0xFF;
				Uint8 b = pixel & 0xFF;
				Uint8 v = (Uint8)(0.212671f * r
					+ 0.715160f * g
					+ 0.072169f * b);
				pixel = (0xFF << 24) | (v << 16) | (v << 8) | v;
				pixels[y * tmp->w + x] = pixel;
			}
		}

		SDL_UpdateTexture(tex, NULL, tmp->pixels, tmp->w * sizeof(Uint32));
		SDL_FreeSurface(tmp);

		return tex;
	}
	return NULL;
}

// Blending Capabilities

void TM::SetAlphaBlending(SDL_Texture*& texture)
{
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
}
void TM::RemoveAlphaBlending(SDL_Texture*& texture)
{
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_NONE);
}
void TM::SetAlpha(SDL_Texture*& texture, Uint8 alpha)
{
	SDL_SetTextureAlphaMod(texture, alpha);
}

// Altering Capabilities

void TM::SetColorMod(SDL_Texture*& texture, Uint8 R, Uint8 G, Uint8 B)
{
	SDL_SetTextureColorMod(texture, R, G, B);
}