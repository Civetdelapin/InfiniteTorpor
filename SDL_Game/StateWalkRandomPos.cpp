#include "StateWalkRandomPos.h"

StateWalkRandomPos::StateWalkRandomPos(GameObject* gameObject, float range, std::string nextState) : State(nextState), range(range)
{
	enemyBasicBehavior = gameObject->getComponent<EnemyBasicBehavior>();
}


StateWalkRandomPos::~StateWalkRandomPos()
{
}

void StateWalkRandomPos::start(StateMachine* state_machine)
{
	vectToGo = OwnMathFuncs::OwnMathFuncs::getRandomPointAroundCircle(range) + state_machine->getGameObject()->getStartPosition();
	state_machine->getGameObject()->getComponent<Animator>()->play("Walking");
}

void StateWalkRandomPos::operation(StateMachine* state_machine)
{

	OwnMathFuncs::Vector2 directionVector = (vectToGo - state_machine->getGameObject()->getWorldPosition());
	OwnMathFuncs::OwnMathFuncs::normalize(directionVector);
	enemyBasicBehavior->addForce(directionVector, enemyBasicBehavior->getSpeed());

	if (OwnMathFuncs::OwnMathFuncs::distanceBetweenVect(vectToGo, state_machine->getGameObject()->getWorldPosition()) <= 20) {
		state_machine->getGameObject()->getComponent<StateMachine>()->play(getNextState());
	}
	
}

void StateWalkRandomPos::exit(StateMachine* state_machine)
{

}
