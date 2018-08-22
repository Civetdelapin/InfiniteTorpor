#pragma once
#include "GameObject.h"
class AnimatedGameObject : public virtual GameObject
	
{
public:
	AnimatedGameObject(SDL_Renderer* renderer, int sprite_size_x, int sprite_size_y, int nb_sprites);
	~AnimatedGameObject();

	void render() override;

private:

	int sprite_size_x, sprite_size_y, nb_sprites;

};

