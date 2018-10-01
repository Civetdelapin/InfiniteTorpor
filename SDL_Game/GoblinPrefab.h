#pragma once
#include "GameObject.h"
#include "Enemy.h"
#include "Animator.h"
#include "StateRushPlayer.h"
#include "EnemyAttackCollider.h"

class GoblinPrefab : public Enemy
{
public:
	GoblinPrefab(OwnMathFuncs::Vector2 init_local_pos = { 0, 0 });
	~GoblinPrefab();
};

