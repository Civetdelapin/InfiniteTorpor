#pragma once
#include "State.h"
#include "EnemyBasicBehavior.h"
#include "StateMachine.h"
#include "StateOnlyWait.h"
#include "Animator.h"

class StateWalkRandomPos : public State
{
public:
	StateWalkRandomPos(GameObject* game_object);
	~StateWalkRandomPos();


	void operation(GameObject* game_object);
	void exit(GameObject* game_object);

private:

	float range = 50;
	OwnMathFuncs::Vector2 vect_to_go = { 0, 0 };

	EnemyBasicBehavior* enemy_basic_behavior;
};

