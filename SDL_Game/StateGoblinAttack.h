#pragma once
#include "State.h"
#include "EnemyBasicBehavior.h"
#include "Animator.h"
#include "StateRushPlayer.h"

class StateGoblinAttack : public State
{
public:
	StateGoblinAttack(GameObject * game_object);
	~StateGoblinAttack();

	float time_attack = 0.5f;
	const float velocity_attack = 300000;

	void operation(GameObject* game_object);

private:
	GameObject * target;
	EnemyBasicBehavior* enemy_basic_behavior;

	float time_passed;
	bool before_attack = true;

	OwnMathFuncs::Vector2 normalize_dir = { 0, 0 };
};

