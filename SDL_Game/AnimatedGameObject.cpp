#include "AnimatedGameObject.h"

AnimatedGameObject::AnimatedGameObject(SDL_Renderer* renderer, int sprite_size_x, int sprite_size_y, int nb_sprites) : GameObject(renderer), sprite_size_x(sprite_size_x), sprite_size_y(sprite_size_y), nb_sprites(nb_sprites)
{

}

AnimatedGameObject::~AnimatedGameObject()
{


}

void AnimatedGameObject::render()
{
	GameObject::render();
}
