#pragma once
#include "GameObject.h"
#include "Game.h"
#include "Map.h"
#include "PlayerController.h"
#include "SpriteRenderer.h"
#include "VelocityBody.h"
#include "Animator.h"
#include "PlayerStat.h"
#include "PlayerAttack.h"

class Player : public GameObject
{
public:
	Player(std::string img_path, OwnMathFuncs::Vector2 sprite_size);
	~Player();

private:
	
	int world_collider_up_offset = 6;
	int world_collider_bottom_offset = 1;
	int world_collider_left_offset = 12;
	int world_collider_right_offset = 12;



};

