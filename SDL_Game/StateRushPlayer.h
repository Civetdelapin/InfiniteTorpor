#pragma once
#include "State.h"
#include "VelocityBody.h"
#include "EnemyBasicBehavior.h"
#include "StateMachine.h"
#include "StateMeleeAttack.h"

class StateRushPlayer : public State
{
public:
	StateRushPlayer(GameObject * game_object, float range, std::string next_state = "");
	~StateRushPlayer();

	void start(StateMachine* state_machine);
	void operation(StateMachine* state_machine);
	void exit(StateMachine* state_machine);

private:
	GameObject * target;
	EnemyBasicBehavior* enemy_basic_behavior;

	float range = 50;
};

