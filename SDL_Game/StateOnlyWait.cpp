#include "StateOnlyWait.h"



StateOnlyWait::StateOnlyWait(GameObject* game_object)
{
	time_passed = time_to_wait;

	game_object->getComponent<Animator>()->play("Idle");
}


StateOnlyWait::~StateOnlyWait()
{
}

void StateOnlyWait::operation(GameObject * game_object)
{
	time_passed -= Time::deltaTime;

	if (time_passed <= 0) {
		game_object->getComponent<StateMachine>()->setState(new StateWalkRandomPos(game_object));
	}
}

void StateOnlyWait::exit(GameObject * game_object)
{

}
