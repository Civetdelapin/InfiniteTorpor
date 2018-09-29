#pragma once
#define _USE_MATH_DEFINES

#include <math.h>

#include "State.h"
#include "EnemyBasicBehavior.h"
#include "Animator.h"
#include "StateRushPlayer.h"
#include "EnemyAttackCollider.h"
#include "SlimProjectilePrefab.h"


class StateSlimAttack : public State
{
public:
	StateSlimAttack(GameObject * game_object, int nb_projectile, std::string next_state = "");
	~StateSlimAttack();

	void start(StateMachine* state_machine);
	void operation(StateMachine* state_machine);
	void exit(StateMachine* state_machine);

	const float time_attack = 0.8f;
	const float time_cd = 0.2f;

private:

	int nb_projectile;
	float time_passed;

	bool attack = false;

	void createProjectiles(StateMachine* state_machine);
};

