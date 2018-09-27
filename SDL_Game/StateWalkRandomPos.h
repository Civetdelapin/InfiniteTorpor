#pragma once
#include "State.h"

class StateWalkRandomPos : public State
{
public:
	StateWalkRandomPos(GameObject* game_object);
	~StateWalkRandomPos();


	void operation(GameObject* game_object);
	void exit(GameObject* game_object);

private:

	float range = 100;

	OwnMathFuncs::Vector2 vect_to_go = { 0, 0 };
};

