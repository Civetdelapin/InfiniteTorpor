#include "StateRushPlayer.h"
#include "Game.h"

StateRushPlayer::StateRushPlayer(GameObject * game_object, float range, std::string next_state) : State(next_state), range(range)
{
	enemy_basic_behavior = game_object->getComponent<EnemyBasicBehavior>();
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
			OwnMathFuncs::Vector2 dir_vect = (target->getWorldPosition() - state_machine->getGameObject()->getWorldPosition());
			OwnMathFuncs::OwnMathFuncs::normalize(dir_vect);

			enemy_basic_behavior->addForce(dir_vect, enemy_basic_behavior->getSpeed());
		}
	}
	else {
		state_machine->getGameObject()->getComponent<StateMachine>()->play(getNextState());
	}
}

void StateRushPlayer::exit(StateMachine* state_machine)
{

}
