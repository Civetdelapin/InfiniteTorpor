#pragma once
#include "State.h"
#include "StateMachine.h"
#include "EnemyBasicBehavior.h"

class StateStun : public State
{
public:
	StateStun(GameObject* game_object, std::string next_state = "");
	~StateStun();


	void start(StateMachine* state_machine);
	void operation(StateMachine* state_machine);
	void exit(StateMachine* state_machine);

private:

	float time_to_wait;
	float timeLeft;
};

