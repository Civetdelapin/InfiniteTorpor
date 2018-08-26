#pragma once
#include "Component.h"
#include "VelocityBody.h"
#include "GameObject.h"
#include "OwnMathFuncs.h"
#include "Animator.h"
#include "BoxCollider.h"

class PlayerController : public virtual Component
{
public:
	PlayerController(GameObject* game_object);
	~PlayerController();

	float speed = 2500;

	bool can_move = true;

	void update();

private:

	VelocityBody* velocityBody;
	Animator* animator;
	BoxCollider* box_collider;
};

