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
	VelocityBody(GameObject* game_object);

	OwnMathFuncs::Vector2 velocity = { 0, 0 };
	OwnMathFuncs::Vector2 drag = { 20, 20};

	void update();

	~VelocityBody();


private:
	Collider * collider;
};

