#pragma once
#include "State.h"
#include "EnemyBasicBehavior.h"
#include "Animator.h"
#include "StateRushPlayer.h"
#include "EnemyAttackCollider.h"


class StateDying : public State
{
public:
	StateDying(GameObject * gameObject, std::string nextState = "");
	~StateDying();

	const float timeAnimation = 1.75f;
	const float timeAlphaToZero = 0.25f;

	void start(StateMachine* state_machine);
	void operation(StateMachine* state_machine);
	void exit(StateMachine* state_machine);

private:

	bool alphaPhase = false;
	float timeLeft;

	Animator* animator;
	SpriteRenderer* spriteRenderer;
};

