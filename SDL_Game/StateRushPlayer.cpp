#include "StateRushPlayer.h"
#include "Game.h"

StateRushPlayer::StateRushPlayer(GameObject * game_object)
{
	enemy_basic_behavior = game_object->getComponent<EnemyBasicBehavior>();
	target = Game::instance()->findGameObject("Player");

	game_object->getComponent<Animator>()->play("Walking");
}


StateRushPlayer::~StateRushPlayer()
{
}

void StateRushPlayer::operation(GameObject * game_object)
{

	if (target != nullptr && !enemy_basic_behavior->isStunned()) {
			
		if (OwnMathFuncs::OwnMathFuncs::distanceBetweenVect(target->getWorldPosition(), game_object->getWorldPosition()) <= 80) {
			game_object->getComponent<StateMachine>()->setState(new StateGoblinAttack(game_object));
		}
		else {
			OwnMathFuncs::Vector2 dir_vect = (target->getWorldPosition() - game_object->getWorldPosition());
			OwnMathFuncs::OwnMathFuncs::normalize(dir_vect);

			enemy_basic_behavior->addForce(dir_vect, enemy_basic_behavior->getSpeed());
		}
	}
}

void StateRushPlayer::exit(GameObject * game_object)
{

}
