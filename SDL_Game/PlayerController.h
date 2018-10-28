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
	PlayerController(GameObject* gameObject);
	~PlayerController();

	const enum State { dashing, ready_dash, cant_dash };

	void setCanMove(bool value);

	void update();

	State getState();

	OwnMathFuncs::Vector2 getDirection();

private:

	VelocityBody* velocityBody;
	Animator* animator;
	BoxCollider* boxCollider;

	bool canMove = true;
	State state = ready_dash;

	float speed = 1000;
	float dashSpeed = 1450;
	float timeDash = 0.5;
	float timeInvisibleDash = 0.5;
	float timeCDDash = 0.10;

	float timeLeft;
	
	OwnMathFuncs::Vector2 normalizeDirection = { 0, 0 };
	OwnMathFuncs::Vector2 direction = { 1, 0 };
};

