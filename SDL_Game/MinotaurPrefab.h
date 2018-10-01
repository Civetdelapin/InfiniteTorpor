#pragma once
#include "Enemy.h"
#include "StateOnlyWait.h"
#include "StateSlimAttack.h"

class MinotaurPrefab :
	public Enemy
{
public:
	MinotaurPrefab(std::string img_path, OwnMathFuncs::Vector2 sprite_size, OwnMathFuncs::Vector2 init_local_pos = { 0, 0 });
	~MinotaurPrefab();
};

