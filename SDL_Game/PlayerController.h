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

	float speed = 2300;
	float dash_speed = 3500;
	float time_dash = 0.30;
	float time_cd_dash = 0.10;

	bool can_move = true;

	void update();


private:

	VelocityBody* velocityBody;
	Animator* animator;
	BoxCollider* box_collider;

	enum State { dashing, ready_dash, cant_dash };
	State state = ready_dash;

	float time_passed;
	
	OwnMathFuncs::Vector2 normalizeDirection = { 0, 0 };

};

