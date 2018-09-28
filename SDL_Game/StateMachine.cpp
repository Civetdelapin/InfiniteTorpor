#include "StateMachine.h"



StateMachine::StateMachine(GameObject* game_object) : Component(game_object)
{

}


StateMachine::~StateMachine()
{
}

void StateMachine::update()
{
	if (cur_state != "") {
		states[cur_state]->operation(this);
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

void StateMachine::play(std::string state_name)
{
	if (cur_state != "") {
		states[cur_state]->exit(this);
	}

	if (states.count(state_name) > 0) {
		cur_state = state_name;
	}
	else {
		cur_state = "";
	}


	if (cur_state != "" ) {
		states[cur_state]->start(this);
	}
}

std::string StateMachine::getDefaultState()
{
	return default_state;
}

void StateMachine::setDefaultState(std::string value)
{
	default_state = value;
}
