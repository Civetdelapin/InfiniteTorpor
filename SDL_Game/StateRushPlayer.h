#pragma once
#include "State.h"
#include "VelocityBody.h"
#include "EnemyBasicBehavior.h"

class StateRushPlayer : public State
{
public:
	StateRushPlayer(GameObject * game_object);
	~StateRushPlayer();

	void operation(GameObject* game_object);

private:
	GameObject * target;
	EnemyBasicBehavior* enemy_basic_behavior;
};

