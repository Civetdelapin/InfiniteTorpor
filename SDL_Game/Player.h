#pragma once
#include "GameObject.h"
#include "Game.h"
#include "PlayerController.h"
#include "SpriteRenderer.h"
#include "VelocityBody.h"
#include "Animator.h"
#include "PlayerBehavior.h"
#include "PlayerAttack.h"

class Player : public GameObject
{
public:
	Player(OwnMathFuncs::Vector2 init_local_pos = { 0, 0 });
	~Player();

private:
	
	int world_collider_up_offset = 6;
	int world_collider_bottom_offset = 1;
	int world_collider_left_offset = 12;
	int world_collider_right_offset = 12;
};

