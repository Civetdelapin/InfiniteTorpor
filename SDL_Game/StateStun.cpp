#include "StateStun.h"



StateStun::StateStun(GameObject* game_object, std::string next_state) : State(next_state), time_to_wait(time_to_wait)
{
}


StateStun::~StateStun()
{
}

void StateStun::start(StateMachine* state_machine)
{
	//state_machine->getGameObject()->getComponent<Animator>()->play("Idle");
	time_passed = state_machine->getGameObject()->getComponent<EnemyBasicBehavior>()->getTimeStun();
}

void StateStun::operation(StateMachine* state_machine)
{
	time_passed -= Time::deltaTime;

	if (time_passed <= 0) {
		state_machine->play(state_machine->getDefaultState());
	}
}

void StateStun::exit(StateMachine* state_machine)
{

}