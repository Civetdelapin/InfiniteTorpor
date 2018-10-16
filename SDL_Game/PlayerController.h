#pragma once
#include "Component.h"
#include "VelocityBody.h"
#include "GameObject.h"
#include "OwnMathFuncs.h"
#include "Animator.h"
#include "BoxCollider.h"
#include "PlayerBehavior.h"

class PlayerController : public virtual Component
{
public:
	PlayerController(GameObject* game_object);
	~PlayerController();

	const enum State { dashing, ready_dash, cant_dash };

	void setCanMove(bool value);

	void update();

	State getState();

	OwnMathFuncs::Vector2 getDirection();

private:

	VelocityBody* velocityBody;
	Animator* animator;
	BoxCollider* box_collider;

	bool can_move = true;
	State state = ready_dash;

	float speed = 1200;
	float dash_speed = 1750;
	float time_dash = 0.35;
	float time_invisible_dash = 0.5;
	float time_cd_dash = 0.10;

	float timeLeft;
	
	OwnMathFuncs::Vector2 normalizeDirection = { 0, 0 };
	OwnMathFuncs::Vector2 direction = { 1, 0 };
};

