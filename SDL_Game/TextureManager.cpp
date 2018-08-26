#include "TextureManager.h"
#include "Game.h"

SDL_Texture * TextureManager::LoadTexture(const char * fileName, int &w, int &h)
{
	SDL_Surface* tempSurface = IMG_Load(fileName);

	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);

	SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	SDL_FreeSurface(tempSurface);
	return texture;
}

SDL_Texture * TextureManager::LoadTexture(const char * fileName)
{
	SDL_Surface* tempSurface = IMG_Load(fileName);

	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);

	SDL_FreeSurface(tempSurface);
	return texture;
}

void TextureManager::DrawTexture(SDL_Texture * texture, SDL_Rect srcrect, SDL_Rect destrect, SDL_RendererFlip render_flip)
{
	SDL_RenderCopyEx(Game::renderer, texture, &srcrect, &destrect, NULL, NULL, render_flip);
}
