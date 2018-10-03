#pragma once
#include "Enemy.h"
#include "StateOnlyWait.h"
#include "StateLaunchProjectile.h"

class SnakePrefab : public Enemy
{
public:
	SnakePrefab(OwnMathFuncs::Vector2 init_local_pos = { 0, 0 });
	~SnakePrefab();
};

