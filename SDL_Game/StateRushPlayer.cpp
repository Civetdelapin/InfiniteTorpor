#include "StateRushPlayer.h"
#include "Game.h"

StateRushPlayer::StateRushPlayer(GameObject * gameObject, float range, std::string nextState) : State(nextState), range(range)
{
	enemyBasicBehavior = gameObject->getComponent<EnemyBasicBehavior>();
}


StateRushPlayer::~StateRushPlayer()
{
}

void StateRushPlayer::start(StateMachine* state_machine)
{
	state_machine->getGameObject()->getComponent<Animator>()->play("Walking");

	target = Game::instance()->findGameObject("Player");
}

void StateRushPlayer::operation(StateMachine* state_machine)
{	
	
	if (target != nullptr) {
			
		if (OwnMathFuncs::OwnMathFuncs::distanceBetweenVect(target->getWorldPosition(), state_machine->getGameObject()->getWorldPosition()) <= range) {

			state_machine->getGameObject()->getComponent<StateMachine>()->play(getNextState());
		}
		else {
			OwnMathFuncs::Vector2 directionVector = (target->getWorldPosition() - state_machine->getGameObject()->getWorldPosition());
			OwnMathFuncs::OwnMathFuncs::normalize(directionVector);

			enemyBasicBehavior->addForce(directionVector, enemyBasicBehavior->getSpeed());
		}
	}
	else {
		state_machine->getGameObject()->getComponent<StateMachine>()->play(getNextState());
	}
}

void StateRushPlayer::exit(StateMachine* state_machine)
{

}
