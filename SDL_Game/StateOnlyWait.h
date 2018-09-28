#pragma once
#include "State.h"
#include "StateMachine.h"
#include "StateWalkRandomPos.h"

class StateOnlyWait : public State
{
public:
	StateOnlyWait(GameObject * game_object, float time_to_wait, std::string next_state = "");
	~StateOnlyWait();

	void start(StateMachine* state_machine);
	void operation(StateMachine* state_machine);
	void exit(StateMachine* state_machine);

private:

	float time_to_wait = 2.0f;
	float time_passed = 0;
};

