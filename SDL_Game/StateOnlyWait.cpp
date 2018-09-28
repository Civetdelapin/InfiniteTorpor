#include "StateOnlyWait.h"

StateOnlyWait::StateOnlyWait(GameObject * game_object, float time_to_wait, std::string next_state) : State(next_state), time_to_wait(time_to_wait)
{
	
}

StateOnlyWait::~StateOnlyWait()
{
}

void StateOnlyWait::start(StateMachine* state_machine)
{
	state_machine->getGameObject()->getComponent<Animator>()->play("Idle");
	time_passed = time_to_wait;
}

void StateOnlyWait::operation(StateMachine* state_machine)
{
	time_passed -= Time::deltaTime;

	if (time_passed <= 0) {
	
		state_machine->getGameObject()->getComponent<StateMachine>()->play(getNextState());
		
	}
}

void StateOnlyWait::exit(StateMachine* state_machine)
{

}
