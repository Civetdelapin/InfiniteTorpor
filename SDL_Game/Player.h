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
	
	int worldColliderUpOffset = 6;
	int worldColliderBottomOffset = 1;
	int worldColliderLeftOffset = 12;
	int worldColliderRightOffset = 12;
};

