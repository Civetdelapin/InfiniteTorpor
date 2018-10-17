#include "StateOnlyWait.h"

StateOnlyWait::StateOnlyWait(GameObject * gameObject, float timeToWait, std::string nextState) : State(nextState), timeToWait(timeToWait)
{
	
}

StateOnlyWait::~StateOnlyWait()
{
}

void StateOnlyWait::start(StateMachine* state_machine)
{
	state_machine->getGameObject()->getComponent<Animator>()->play("Idle");
	timeLeft = timeToWait;
}

void StateOnlyWait::operation(StateMachine* state_machine)
{
	timeLeft -= Time::deltaTime;

	if (timeLeft <= 0) {
	
		state_machine->getGameObject()->getComponent<StateMachine>()->play(getNextState());
		
	}
}

void StateOnlyWait::exit(StateMachine* state_machine)
{

}
