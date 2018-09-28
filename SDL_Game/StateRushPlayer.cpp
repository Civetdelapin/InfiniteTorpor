#include "StateRushPlayer.h"
#include "Game.h"

StateRushPlayer::StateRushPlayer(GameObject * game_object, std::string next_state) : State(next_state)
{
	enemy_basic_behavior = game_object->getComponent<EnemyBasicBehavior>();
	target = Game::instance()->findGameObject("Player");

}


StateRushPlayer::~StateRushPlayer()
{
}

void StateRushPlayer::start(StateMachine* state_machine)
{
	state_machine->getGameObject()->getComponent<Animator>()->play("Walking");
}

void StateRushPlayer::operation(StateMachine* state_machine)
{

	if (target != nullptr) {
			
		if (OwnMathFuncs::OwnMathFuncs::distanceBetweenVect(target->getWorldPosition(), state_machine->getGameObject()->getWorldPosition()) <= 80) {

			state_machine->getGameObject()->getComponent<StateMachine>()->play(getNextState());
		}
		else {
			OwnMathFuncs::Vector2 dir_vect = (target->getWorldPosition() - state_machine->getGameObject()->getWorldPosition());
			OwnMathFuncs::OwnMathFuncs::normalize(dir_vect);

			enemy_basic_behavior->addForce(dir_vect, enemy_basic_behavior->getSpeed());
		}
	}
}

void StateRushPlayer::exit(StateMachine* state_machine)
{

}
