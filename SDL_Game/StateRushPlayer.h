#pragma once
#include "State.h"
#include "VelocityBody.h"
#include "EnemyBasicBehavior.h"
#include "StateMachine.h"
#include "StateMeleeAttack.h"

class StateRushPlayer : public State
{
public:
	StateRushPlayer(GameObject * gameObject, float range, std::string nextState = "");
	~StateRushPlayer();

	void start(StateMachine* state_machine);
	void operation(StateMachine* state_machine);
	void exit(StateMachine* state_machine);

private:
	GameObject * target;
	EnemyBasicBehavior* enemyBasicBehavior;

	OwnMathFuncs::Vector2 positionToGo = { 0, 0 };
	
	void findNewPosition(StateMachine* state_machine);

	float range = 50;
};

