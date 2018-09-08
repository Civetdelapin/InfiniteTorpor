#include "StateRushPlayer.h"
#include "Game.h"

StateRushPlayer::StateRushPlayer(GameObject * game_object)
{
	enemy_basic_behavior = game_object->getComponent<EnemyBasicBehavior>();
	target = Game::instance()->findGameObject("Player");
}


StateRushPlayer::~StateRushPlayer()
{
}

void StateRushPlayer::operation(GameObject * game_object)
{

	if (target != nullptr) {
			
		OwnMathFuncs::Vector2 dir_vect = (target->getWorldPosition() - game_object->getWorldPosition());
		OwnMathFuncs::OwnMathFuncs::normalize(dir_vect);

		enemy_basic_behavior->addForce(dir_vect, 2300);
	}
	
}
