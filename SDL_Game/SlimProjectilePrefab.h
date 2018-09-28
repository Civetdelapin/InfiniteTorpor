#pragma once
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "BoxCollider.h"
#include "ProjectileBehavior.h"
#include "EnemyAttackCollider.h"

class SlimProjectilePrefab : public GameObject
{
public:
	SlimProjectilePrefab(OwnMathFuncs::Vector2 init_local_pos = { 0, 0 });
	~SlimProjectilePrefab();
};

