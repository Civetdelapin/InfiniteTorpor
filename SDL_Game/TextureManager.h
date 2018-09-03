#pragma once
#include "SDL.h"
#include "SDL_image.h"

class TextureManager
{
public:

	static SDL_Texture* LoadTexture(const char* fileName, int &w, int &h);

	static SDL_Texture * LoadTexture(const char * fileName);

	static void DrawTexture(SDL_Texture* texture, SDL_Rect srcrect, SDL_Rect destrect, SDL_RendererFlip render_flip = SDL_FLIP_NONE, bool is_relative_to_camera = true);

	static void DrawRect(SDL_Rect rect, int r = 255, int g = 0, int b = 0, int a = 255, bool is_fill = false);
};

