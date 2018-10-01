#pragma once
#include "Enemy.h"
#include "StateOnlyWait.h"
#include "StateSlimAttack.h"

class MinotaurPrefab :
	public Enemy
{
public:
	MinotaurPrefab(OwnMathFuncs::Vector2 init_local_pos = { 0, 0 });
	~MinotaurPrefab();
};

