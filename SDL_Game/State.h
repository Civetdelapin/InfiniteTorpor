#pragma once
#include <iostream>
#include <string>

class StateMachine;

class State {

public:

	State(std::string next_state = "");
	~State();

	virtual void start(StateMachine* state_machine) = 0;
	virtual void operation(StateMachine* state_machine) = 0;
	virtual void exit(StateMachine* state_machine) = 0;

	std::string getNextState();

private:
	std::string next_state = "";
};