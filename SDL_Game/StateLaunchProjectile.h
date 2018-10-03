#pragma once
#include "State.h"
#include "StateMachine.h"
#include "EnemyBasicBehavior.h"
#include "Animator.h"
#include "SlimProjectilePrefab.h"

class StateLaunchProjectile : public State
{
public:
	StateLaunchProjectile(GameObject* game_object, std::string next_state = "");
	~StateLaunchProjectile();

	void start(StateMachine* state_machine);
	void operation(StateMachine* state_machine);
	void exit(StateMachine* state_machine);

private:
	float time_attack = 0.8f;
	float time_cd = 0.6f;

	float time_left;

	bool before_attack = false;

	OwnMathFuncs::Vector2 dir_vect = { 0, 0 };

	GameObject* target = nullptr;
};

