#include "TextureManager.h"
#include "Game.h"

SDL_Texture * TextureManager::LoadTexture(const char * fileName, int &w, int &h)
{
	SDL_Surface* tempSurface = IMG_Load(fileName);

	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::instance()->renderer, tempSurface);

	SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	SDL_FreeSurface(tempSurface);
	return texture;
}

SDL_Texture * TextureManager::LoadTexture(const char * fileName)
{
	SDL_Surface* tempSurface = IMG_Load(fileName);

	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::instance()->renderer, tempSurface);

	SDL_FreeSurface(tempSurface);
	return texture;
}

void TextureManager::DrawTexture(SDL_Texture * texture, SDL_Rect srcrect, SDL_Rect destrect, SDL_RendererFlip render_flip, bool is_relative_to_camera)
{
	if (is_relative_to_camera) {
		destrect.x -= Camera::camera_pos_x;
		destrect.y -= Camera::camera_pos_y;
	}
	
	SDL_RenderCopyEx(Game::instance()->renderer, texture, &srcrect, &destrect, NULL, NULL, render_flip);
}

void TextureManager::DrawRect(SDL_Rect rect, int r, int g, int b, int a, bool is_fill)
{
	rect.x -= Camera::camera_pos_x;
	rect.y -= Camera::camera_pos_y;

	SDL_SetRenderDrawColor(Game::instance()->renderer, r, g, b, a);

	if (is_fill) {
		SDL_RenderFillRect(Game::instance()->renderer, &rect);
	}
	else {
		SDL_RenderDrawRect(Game::instance()->renderer, &rect);
	}
}
