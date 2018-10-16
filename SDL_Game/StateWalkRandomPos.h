#pragma once
#include "State.h"
#include "EnemyBasicBehavior.h"
#include "StateMachine.h"
#include "StateOnlyWait.h"
#include "Animator.h"

class StateWalkRandomPos : public State
{
public:
	StateWalkRandomPos(GameObject* gameObject, float range, std::string next_state = "");
	~StateWalkRandomPos();

	void start(StateMachine* state_machine);
	void operation(StateMachine* state_machine);
	void exit(StateMachine* state_machine);

private:

	float range = 50;
	OwnMathFuncs::Vector2 vect_to_go = { 0, 0 };

	EnemyBasicBehavior* enemy_basic_behavior;
};

