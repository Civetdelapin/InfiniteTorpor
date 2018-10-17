#pragma once
#include "State.h"
#include "EnemyBasicBehavior.h"
#include "Animator.h"
#include "StateRushPlayer.h"
#include "EnemyAttackCollider.h"

class StateMeleeAttack : public State
{
public:
	StateMeleeAttack(GameObject * gameObject, std::string nextState = "", float timeAttack = 0.5f, float velocityAttack = 900);
	~StateMeleeAttack();
 
	void start(StateMachine* state_machine);
	void operation(StateMachine* state_machine);
	void exit(StateMachine* state_machine);

private:
	GameObject * target;
	EnemyBasicBehavior* enemyBasicBehavior;
	Collider* colliderActive;

	float timeLeft;
	bool beforeAttack = true;

	float timeAttack;
	float velocityAttack;

	OwnMathFuncs::Vector2 normalizeDirection = { 0, 0 };
};

