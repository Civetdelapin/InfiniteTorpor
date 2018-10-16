#include "StateStun.h"



StateStun::StateStun(GameObject* gameObject, std::string next_state) : State(next_state), time_to_wait(time_to_wait)
{
}


StateStun::~StateStun()
{
}

void StateStun::start(StateMachine* state_machine)
{
	//state_machine->getGameObject()->getComponent<Animator>()->play("Idle");
	timeLeft = state_machine->getGameObject()->getComponent<EnemyBasicBehavior>()->getTimeStun();
}

void StateStun::operation(StateMachine* state_machine)
{
	timeLeft -= Time::deltaTime;

	if (timeLeft <= 0) {
		state_machine->play(state_machine->getDefaultState());
	}
}

void StateStun::exit(StateMachine* state_machine)
{

}