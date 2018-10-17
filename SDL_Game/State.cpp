#include "State.h"
#include "StateMachine.h"

State::State(std::string nextState) : nextState(nextState)
{

}

State::~State()
{
}

std::string State::getNextState()
{
	return nextState;
}
