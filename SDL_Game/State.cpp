#include "State.h"
#include "StateMachine.h"

State::State(std::string next_state) : next_state(next_state)
{

}

State::~State()
{
}

std::string State::getNextState()
{
	return next_state;
}
