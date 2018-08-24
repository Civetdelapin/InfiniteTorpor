#include "GameObject.h"

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
	

	position.x += (velocity.x * Time::deltaTime);
	position.y += (velocity.y * Time::deltaTime);

	dstrect.x = position.x;
	dstrect.y = position.y;
}

void GameObject::render()
{
	if (texture != nullptr) {

		dstrect.w = sprite_sizeX;
		dstrect.h = sprite_sizeY;

		srcrect.w = sprite_sizeX;
		srcrect.h = sprite_sizeY;

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


