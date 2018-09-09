#pragma once
#include "State.h"
#include "VelocityBody.h"
#include "EnemyBasicBehavior.h"
#include "StateMachine.h"
#include "StateGoblinAttack.h"

class StateRushPlayer : public State
{
public:
	StateRushPlayer(GameObject * game_object);
	~StateRushPlayer();

	void operation(GameObject* game_object);
	void exit(GameObject* game_object);

private:
	GameObject * target;
	EnemyBasicBehavior* enemy_basic_behavior;

	
};

