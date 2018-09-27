#pragma once
#include "State.h"
#include "EnemyBasicBehavior.h"
#include "Animator.h"
#include "StateRushPlayer.h"
#include "EnemyAttackCollider.h"

class StateGoblinAttack : public State
{
public:
	StateGoblinAttack(GameObject * game_object);
	~StateGoblinAttack();

	const float time_attack = 0.5f;
	const float velocity_attack = 300000;

	void operation(GameObject* game_object);
	void exit(GameObject* game_object);

private:
	GameObject * target;
	EnemyBasicBehavior* enemy_basic_behavior;
	Collider* collider_active;

	float time_passed;
	bool before_attack = true;

	OwnMathFuncs::Vector2 normalize_dir = { 0, 0 };
};

