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

private:

	int nb_projectile;
};

