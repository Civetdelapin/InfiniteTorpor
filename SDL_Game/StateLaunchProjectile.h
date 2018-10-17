#pragma once
#include "State.h"
#include "StateMachine.h"
#include "EnemyBasicBehavior.h"
#include "Animator.h"
#include "SlimProjectilePrefab.h"

class StateLaunchProjectile : public State
{
public:
	StateLaunchProjectile(GameObject* gameObject, std::string nextState = "");
	~StateLaunchProjectile();

	void start(StateMachine* state_machine);
	void operation(StateMachine* state_machine);
	void exit(StateMachine* state_machine);

private:
	float timeAttack = 0.8f;
	float timeCd = 0.6f;

	float timeLeft;

	bool beforeAttack = false;

	OwnMathFuncs::Vector2 directionVector = { 0, 0 };

	GameObject* target = nullptr;
};

