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

		dstrect.x = position.x;
		dstrect.y = position.y;
		dstrect.w = img_size.x;
		dstrect.h = img_size.y;

		srcrect.w = img_size.x;
		srcrect.h = img_size.y;

		SDL_RenderCopy(renderer, texture, &srcrect, &dstrect);
	}
}

void GameObject::clean()
{
	SDL_DestroyTexture(texture);
}

void GameObject::setTexture(SDL_Texture* text)
{
	texture = text;
}
