#pragma once
#include "GameObject.h"
#include "Game.h"

class Player : public virtual GameObject
{
public:
	Player(SDL_Renderer* renderer);
	~Player();

	void update();

private:
	double speed = 0.25;
};

