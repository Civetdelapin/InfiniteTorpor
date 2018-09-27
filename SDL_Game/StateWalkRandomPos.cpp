#include "StateWalkRandomPos.h"



StateWalkRandomPos::StateWalkRandomPos(GameObject* game_object)
{
	vect_to_go = OwnMathFuncs::OwnMathFuncs::getRandomPointInCircle(range);
}


StateWalkRandomPos::~StateWalkRandomPos()
{
}

void StateWalkRandomPos::operation(GameObject * game_object)
{

}

void StateWalkRandomPos::exit(GameObject * game_object)
{

}
