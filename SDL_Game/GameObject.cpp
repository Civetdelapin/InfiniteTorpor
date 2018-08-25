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
}

void GameObject::render(float camera_pos_x, float camera_pos_y)
{
	if (texture != nullptr) {

		dstrect.x = (position.x - camera_pos_x - (sprite_sizeX/2) * scale_factor);
		dstrect.y = (position.y - camera_pos_y - (sprite_sizeY/2) * scale_factor);

		dstrect.w = sprite_sizeX * scale_factor;
		dstrect.h = sprite_sizeY * scale_factor;

		srcrect.w = sprite_sizeX;
		srcrect.h = sprite_sizeY;

		SDL_RendererFlip flip = SDL_FLIP_NONE;
		if (isFlipped) {
			flip = SDL_FLIP_HORIZONTAL;
		}

		TextureManager::DrawTexture(texture, renderer, srcrect, dstrect, flip);
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


