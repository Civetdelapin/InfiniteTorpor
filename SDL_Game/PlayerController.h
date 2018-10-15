#pragma once
#include "Component.h"
#include "VelocityBody.h"
#include "GameObject.h"
#include "OwnMathFuncs.h"
#include "Animator.h"
#include "BoxCollider.h"
#include "PlayerStat.h"

class PlayerController : public virtual Component
{
public:
	PlayerController(GameObject* game_object);
	~PlayerController();

	const enum State { dashing, ready_dash, cant_dash };

	const float speed = 1200;
	const float dash_speed = 1750;
	const float time_dash = 0.35;
	const float time_cd_dash = 0.10;

	bool can_move = true;

	void update();

	State getState();

	OwnMathFuncs::Vector2 getDirection();

private:

	VelocityBody* velocityBody;
	Animator* animator;
	BoxCollider* box_collider;

	
	State state = ready_dash;

	float time_passed;
	
	OwnMathFuncs::Vector2 normalizeDirection = { 0, 0 };
	OwnMathFuncs::Vector2 direction = { 1, 0 };
};

