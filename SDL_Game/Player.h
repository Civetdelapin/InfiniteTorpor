#pragma once
#include "GameObject.h"

class Player : public virtual GameObject
{
public:
	Player(SDL_Renderer* renderer);
	~Player();
};

