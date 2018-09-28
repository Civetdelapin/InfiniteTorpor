#include "StateMachine.h"



StateMachine::StateMachine(GameObject* game_object) : Component(game_object)
{

}


StateMachine::~StateMachine()
{
}

void StateMachine::update()
{
	if (cur_state != nullptr) {
		cur_state->operation(game_object);
	}
}

void StateMachine::clean()
{
	delete cur_state;
	cur_state = NULL;

	Component::clean();
}

void StateMachine::setState(State * state) 
{
	if (cur_state != nullptr) {
		cur_state->exit(game_object);
	}
	
	delete cur_state;
	cur_state = state;
}
