#include "StateWalkRandomPos.h"



StateWalkRandomPos::StateWalkRandomPos(GameObject* game_object)
{
	vect_to_go = OwnMathFuncs::OwnMathFuncs::getRandomPointInCircle(range) + game_object->getStartPosition();
	enemy_basic_behavior = game_object->getComponent<EnemyBasicBehavior>();

	game_object->getComponent<Animator>()->play("Walking");
}


StateWalkRandomPos::~StateWalkRandomPos()
{
}

void StateWalkRandomPos::operation(GameObject * game_object)
{

	OwnMathFuncs::Vector2 dir_vect = (vect_to_go - game_object->getWorldPosition());
	OwnMathFuncs::OwnMathFuncs::normalize(dir_vect);
	enemy_basic_behavior->addForce(dir_vect, enemy_basic_behavior->getSpeed());

	if (OwnMathFuncs::OwnMathFuncs::distanceBetweenVect(vect_to_go, game_object->getWorldPosition()) <= 20) {
		game_object->getComponent<StateMachine>()->setState(new StateOnlyWait(game_object));
	}
	
}

void StateWalkRandomPos::exit(GameObject * game_object)
{

}
