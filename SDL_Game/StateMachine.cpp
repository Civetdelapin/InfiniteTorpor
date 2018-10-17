#include "StateMachine.h"



StateMachine::StateMachine(GameObject* gameObject) : Component(gameObject)
{

}


StateMachine::~StateMachine()
{
}

void StateMachine::start()
{
	if (currentState != "") {
		states[currentState]->start(this);
	}
}

void StateMachine::update()
{
	if (currentState != "") {
		states[currentState]->operation(this);
	}
}

void StateMachine::clean()
{

	for (std::map < std::string, State* > ::iterator it = states.begin(); it != states.end(); ++it) {
		//delete the pointer to State
		delete it->second;
	}	
	states.clear();

	Component::clean();
}

void StateMachine::addState(std::pair<std::string, State*> state)
{
	states.insert(state);
}

void StateMachine::play(std::string stateName)
{
	if (currentState != "") {
		states[currentState]->exit(this);
	}

	if (states.count(stateName) > 0) {
		currentState = stateName;
	}
	else {
		currentState = "";
	}


	if (getHasStart() && currentState != "" ) {
		states[currentState]->start(this);
	}
}

std::string StateMachine::getDefaultState()
{
	return defaultState;
}

void StateMachine::setDefaultState(std::string value)
{
	defaultState = value;
}
