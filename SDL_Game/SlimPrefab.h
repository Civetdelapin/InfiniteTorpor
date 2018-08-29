#pragma once
#include "Enemy.h"
#include "Animator.h"
class SlimPrefab : public Enemy
{
public:
	SlimPrefab(std::string img_path, OwnMathFuncs::Vector2* sprite_size);
	~SlimPrefab();
};

