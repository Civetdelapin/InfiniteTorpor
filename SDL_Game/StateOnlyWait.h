#pragma once
#include "State.h"
#include "StateMachine.h"
#include "StateWalkRandomPos.h"

class StateOnlyWait : public State
{
public:
	StateOnlyWait(GameObject * gameObject, float timeToWait, std::string nextState = "");
	~StateOnlyWait();

	void start(StateMachine* state_machine);
	void operation(StateMachine* state_machine);
	void exit(StateMachine* state_machine);

private:

	float timeToWait = 2.0f;
	float timeLeft = 0;
};

