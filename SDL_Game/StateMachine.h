#pragma once
#include "Component.h"
#include "State.h"

class StateMachine : public Component
{
public:
	StateMachine(GameObject* game_object);
	~StateMachine();

	void update();

	void setSet(State* state);
	

private:

	State* cur_state = nullptr;
};

