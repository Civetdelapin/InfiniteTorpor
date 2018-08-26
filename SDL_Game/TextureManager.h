#pragma once
#include "SDL.h"
#include "SDL_image.h"

class TextureManager
{
public:

	static SDL_Texture* LoadTexture(const char* fileName, int &w, int &h);

	static SDL_Texture * LoadTexture(const char * fileName);

	static void DrawTexture(SDL_Texture* texture, SDL_Rect srcrect, SDL_Rect destrect, SDL_RendererFlip render_flip = SDL_FLIP_NONE);
};

