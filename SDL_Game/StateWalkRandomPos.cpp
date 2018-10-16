#include "StateWalkRandomPos.h"

StateWalkRandomPos::StateWalkRandomPos(GameObject* gameObject, float range, std::string next_state) : State(next_state), range(range)
{
	enemy_basic_behavior = gameObject->getComponent<EnemyBasicBehavior>();
}


StateWalkRandomPos::~StateWalkRandomPos()
{
}

void StateWalkRandomPos::start(StateMachine* state_machine)
{
	vect_to_go = OwnMathFuncs::OwnMathFuncs::getRandomPointAroundCircle(range) + state_machine->getGameObject()->getStartPosition();
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
