#pragma once
#include "Component.h"
#include "State.h"
#include <map>

class StateMachine : public Component
{
public:
	StateMachine(GameObject* gameObject);
	~StateMachine();

	void start();
	void update();
	void clean();

	void addState(std::pair <std::string, State*> state);

	void play(std::string stateName);

	std::string getDefaultState();
	void setDefaultState(std::string value);

private:
	std::map <std::string, State*> states;
	std::string currentState = "";

	std::string defaultState = "";
};

