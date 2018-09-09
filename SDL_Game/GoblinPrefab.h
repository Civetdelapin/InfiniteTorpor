#pragma once
#include "GameObject.h"
#include "Enemy.h"
#include "Animator.h"
#include "StateRushPlayer.h"
#include "EnemyAttackCollider.h"

class GoblinPrefab : public Enemy
{
public:
	GoblinPrefab(std::string img_path, OwnMathFuncs::Vector2* sprite_size);
	~GoblinPrefab();
};

