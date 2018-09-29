#pragma once
#include "State.h"
#include "EnemyBasicBehavior.h"
#include "Animator.h"
#include "StateRushPlayer.h"
#include "EnemyAttackCollider.h"


class StateDying : public State
{
public:
	StateDying(GameObject * game_object, std::string next_state = "");
	~StateDying();

	const float time_animation = 1.75f;
	const float time_alpha_0 = 0.25f;

	void start(StateMachine* state_machine);
	void operation(StateMachine* state_machine);
	void exit(StateMachine* state_machine);

private:

	bool is_alpha_phase = false;
	float time_passed;

	Animator* animator;
	SpriteRenderer* sprite_renderer;
};

