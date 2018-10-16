#pragma once
#include "Component.h"
#include "Collider.h"

class ProjectileBehavior : public Component
{
public:
	ProjectileBehavior(GameObject* gameObject, float speed , Collider* hitbox_collider = nullptr);
	~ProjectileBehavior();

	void setDirection(OwnMathFuncs::Vector2 value);
	
	void setSpeed(float value);
	float getSpeed();

	void update();

private:
	float speed = 50;
	OwnMathFuncs::Vector2 direction = { 0, 0 };

	Collider* hitbox_collider;
};

