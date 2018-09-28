#include "StateWalkRandomPos.h"

StateWalkRandomPos::StateWalkRandomPos(GameObject* game_object, std::string next_state) : State(next_state)
{
	enemy_basic_behavior = game_object->getComponent<EnemyBasicBehavior>();
}


StateWalkRandomPos::~StateWalkRandomPos()
{
}

void StateWalkRandomPos::start(StateMachine* state_machine)
{
	vect_to_go = OwnMathFuncs::OwnMathFuncs::getRandomPointInCircle(range) + state_machine->getGameObject()->getStartPosition();
	state_machine->getGameObject()->getComponent<Animator>()->play("Walking");
}

void StateWalkRandomPos::operation(StateMachine* state_machine)
{

	OwnMathFuncs::Vector2 dir_vect = (vect_to_go - state_machine->getGameObject()->getWorldPosition());
	OwnMathFuncs::OwnMathFuncs::normalize(dir_vect);
	enemy_basic_behavior->addForce(dir_vect, enemy_basic_behavior->getSpeed());

	if (OwnMathFuncs::OwnMathFuncs::distanceBetweenVect(vect_to_go, state_machine->getGameObject()->getWorldPosition()) <= 20) {
		state_machine->getGameObject()->getComponent<StateMachine>()->play(getNextState());
	}
	
}

void StateWalkRandomPos::exit(StateMachine* state_machine)
{

}
