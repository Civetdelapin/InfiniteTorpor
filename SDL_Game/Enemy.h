#pragma once
#include "GameObject.h"
#include "VelocityBody.h"
#include "BoxCollider.h"
#include "SpriteRenderer.h"
#include "EnemyBasicBehavior.h"
#include "DisplayEnemyHp.h"
#include "StateMachine.h"

class Enemy : public GameObject
{
public:
	Enemy(std::string img_path, OwnMathFuncs::Vector2 sprite_size);
	~Enemy();
};

