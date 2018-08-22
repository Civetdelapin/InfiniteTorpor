#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(SDL_Renderer* renderer) : renderer(renderer)
{

}

GameObject::~GameObject()
{
}

void GameObject::handleEvents()
{
}

void GameObject::update()
{



}

void GameObject::render()
{
	if (texture != nullptr) {
		SDL_RenderCopy(renderer, texture, &srcrect, &dstrect);
	}
}

void GameObject::clean()
{
	SDL_DestroyTexture(texture);
}
