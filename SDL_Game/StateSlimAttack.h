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
	StateSlimAttack(GameObject * gameObject, int nbProjectile, std::string nextState = "");
	~StateSlimAttack();

	void start(StateMachine* state_machine);
	void operation(StateMachine* state_machine);
	void exit(StateMachine* state_machine);

	const float timeAttack = 0.8f;
	const float timeCd = 0.2f;

private:

	int nbProjectile;
	float timeLeft;

	bool attack = false;

	void createProjectiles(StateMachine* state_machine);
};

