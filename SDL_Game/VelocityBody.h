#pragma once
#include "Component.h"
#include "Collider.h"
#include <cstdint>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <random>

class VelocityBody : public Component
{
public:
	VelocityBody(GameObject* gameObject);
	~VelocityBody();

	void update();

	void setVelocity(OwnMathFuncs::Vector2 value);
	OwnMathFuncs::Vector2 getVelocity();

	void setDrag(OwnMathFuncs::Vector2 value);
	OwnMathFuncs::Vector2 getDrag();

	void AddForce(OwnMathFuncs::Vector2 direction, float power);

	OwnMathFuncs::Vector2 getColliderWorldPosition();

	void resetVelocity();

private:
	Collider * collider;

	OwnMathFuncs::Vector2 velocity = { 0, 0 };
	OwnMathFuncs::Vector2 drag = { 15, 15 };
};

