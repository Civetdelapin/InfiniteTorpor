#include "GameObject.h"
#include "Component.h"

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
	for (Component* component : components) {
		component->update();
	}

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
void GameObject::addComponent(Component * component)
{
	components.push_back(component);
}

template <class T>
void GameObject::removeComponent()
{
	int idFound = -1;
	for (int i = 0; i < components.size(); i++) {

		T *t = (T *)components[i];

		if (f != 0) {
			idFound = i;
			i = components.size();
		}
	}

	if (idFound >= 0) {
		vec.erase(vec.begin() + idFound);
	}
}


template <class T>
Component * GameObject::getComponent()
{
	
	for (Component* component : components) {

		T *t = (T *)component;

		if (f != 0) {
			return component;
		}

	}

	return nullptr;
}


