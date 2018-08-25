#pragma once
#include "GameObject.h"
#include "Game.h"
#include "Map.h"

class Player : public virtual GameObject
{
public:
	Player(SDL_Renderer* renderer, Map* test_map);
	~Player();

	void update();

private:
	Map* test_map;
	double speed = 0.5;
};

