#include "TextureManager.h"
#include "Game.h"

SDL_Texture * TextureManager::LoadTexture(const char * fileName, int &w, int &h)
{
	SDL_Surface* tempSurface = IMG_Load(fileName);
	if (tempSurface != NULL) {
		SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::instance()->renderer, tempSurface);

		SDL_QueryTexture(texture, NULL, NULL, &w, &h);

		SDL_FreeSurface(tempSurface);

		return texture;
	}
	
	return nullptr;
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
		destrect.x -= Game::instance()->getCamera()->getCameraPos().x;
		destrect.y -= Game::instance()->getCamera()->getCameraPos().y;
	}
	SDL_RenderCopyEx(Game::instance()->renderer, texture, &srcrect, &destrect, NULL, NULL, render_flip);

	
}

void TextureManager::DrawRect(SDL_Rect rect, int r, int g, int b, int a, bool is_fill, bool is_relative_to_camera)
{
	if (is_relative_to_camera) {
		rect.x -= Game::instance()->getCamera()->getCameraPos().x;
		rect.y -= Game::instance()->getCamera()->getCameraPos().y;
	}

	SDL_SetRenderDrawColor(Game::instance()->renderer, r, g, b, a);

	if (is_fill) {
		SDL_RenderFillRect(Game::instance()->renderer, &rect);
	}
	else {
		SDL_RenderDrawRect(Game::instance()->renderer, &rect);
	}
}

void TextureManager::DrawText(TTF_Font* font, SDL_Rect rect, std::string message, int r, int g, int b, int a, bool is_relative_to_camera)
{
	if (is_relative_to_camera) {
		
		rect.x -= Game::instance()->getCamera()->getCameraPos().x;
		rect.y -= Game::instance()->getCamera()->getCameraPos().y;
	}
	
	if (font != NULL) {
		SDL_Color newColor = { r, g, b, a };

		SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, message.c_str(), newColor);
		SDL_Texture* messageTexture = SDL_CreateTextureFromSurface(Game::instance()->renderer, surfaceMessage);

		rect.w = surfaceMessage->w;
		rect.h = surfaceMessage->h;

		SDL_RenderCopy(Game::instance()->renderer, messageTexture, NULL, &rect);

		SDL_FreeSurface(surfaceMessage);
		SDL_DestroyTexture(messageTexture);
	}
}
