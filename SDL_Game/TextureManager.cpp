#include "TextureManager.h"

SDL_Texture * TextureManager::LoadTexture(const char * fileName, SDL_Renderer * renderer, int &w, int &h)
{
	SDL_Surface* tempSurface = IMG_Load(fileName);

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);

	SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	SDL_FreeSurface(tempSurface);
	return texture;
}

void TextureManager::DrawTexture(SDL_Texture * texture, SDL_Renderer * renderer, SDL_Rect srcrect, SDL_Rect destrect, SDL_RendererFlip render_flip)
{
	SDL_RenderCopyEx(renderer, texture, &srcrect, &destrect, NULL, NULL, render_flip);
}
