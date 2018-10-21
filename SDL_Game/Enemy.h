#pragma once
#include "GameObject.h"
#include "VelocityBody.h"
#include "BoxCollider.h"
#include "SpriteRenderer.h"
#include "EnemyBasicBehavior.h"
#include "DisplayEnemyHp.h"
#include "StateMachine.h"
#include "StateStun.h"
#include "StateDying.h"
#include "RendererManager.h"

class Enemy : public GameObject
{
public:
	Enemy(std::string img_path, OwnMathFuncs::Vector2 spriteSize, OwnMathFuncs::Vector2 init_local_pos = { 0, 0 });
	virtual ~Enemy();
};

