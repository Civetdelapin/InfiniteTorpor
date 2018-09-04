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

void StateMachine::setSet(State * state) 
{
	cur_state = state;
}
