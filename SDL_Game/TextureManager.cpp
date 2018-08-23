#include "TextureManager.h"

SDL_Texture * TextureManager::LoadTexture(const char * fileName, SDL_Renderer * renderer, int &w, int &h)
{
	SDL_Surface* tempSurface = IMG_Load(fileName);

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);

	SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	SDL_FreeSurface(tempSurface);
	return texture;
}
