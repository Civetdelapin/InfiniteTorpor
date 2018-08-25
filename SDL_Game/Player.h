#pragma once
#include "GameObject.h"
#include "Game.h"
#include "Map.h"
#include "PlayerController.h"

class Player : public virtual GameObject
{
public:
	Player(SDL_Renderer* renderer, Map* test_map);
	~Player();

	void update();

private:
	Map* test_map;
	

	int world_collider_up_offset = 6;
	int world_collider_bottom_offset = 1;
	int world_collider_left_offset = 12;
	int world_collider_right_offset = 12;
};

