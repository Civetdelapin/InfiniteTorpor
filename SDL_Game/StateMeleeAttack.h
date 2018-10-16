#pragma once
#include "State.h"
#include "EnemyBasicBehavior.h"
#include "Animator.h"
#include "StateRushPlayer.h"
#include "EnemyAttackCollider.h"

class StateMeleeAttack : public State
{
public:
	StateMeleeAttack(GameObject * game_object, std::string next_state = "", float time_attack = 0.5f, float velocity_attack = 900);
	~StateMeleeAttack();
 
	void start(StateMachine* state_machine);
	void operation(StateMachine* state_machine);
	void exit(StateMachine* state_machine);

private:
	GameObject * target;
	EnemyBasicBehavior* enemy_basic_behavior;
	Collider* collider_active;

	float timeLeft;
	bool before_attack = true;

	float time_attack;
	float velocity_attack;

	OwnMathFuncs::Vector2 normalize_dir = { 0, 0 };
};

