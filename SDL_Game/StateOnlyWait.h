#pragma once
#include "State.h"
#include "StateMachine.h"
#include "StateWalkRandomPos.h"

class StateOnlyWait : public State
{
public:
	StateOnlyWait(GameObject* game_object);
	~StateOnlyWait();

	void operation(GameObject* game_object);
	void exit(GameObject* game_object);

private:

	float time_to_wait = 2.0f;
	float time_passed = 0;
};

