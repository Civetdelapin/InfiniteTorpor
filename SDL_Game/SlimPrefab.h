#pragma once
#include "Enemy.h"
#include "Animator.h"
#include "StateWalkRandomPos.h"
#include "StateOnlyWait.h"
#include "StateSlimAttack.h"

class SlimPrefab : public Enemy
{
public:
	SlimPrefab(OwnMathFuncs::Vector2 init_local_pos = { 0, 0 });
	~SlimPrefab();
};

