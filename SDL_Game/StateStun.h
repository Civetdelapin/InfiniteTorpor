#pragma once
#include "State.h"
#include "StateMachine.h"
#include "EnemyBasicBehavior.h"

class StateStun : public State
{
public:
	StateStun(GameObject* gameObject, std::string nextState = "");
	~StateStun();


	void start(StateMachine* state_machine);
	void operation(StateMachine* state_machine);
	void exit(StateMachine* state_machine);

private:

	float timeToWait;
	float timeLeft;
};

