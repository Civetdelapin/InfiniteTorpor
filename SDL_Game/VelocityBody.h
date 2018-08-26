#pragma once
#include "Component.h"

class VelocityBody : public Component
{
public:
	VelocityBody(GameObject* game_object);

	OwnMathFuncs::Vector2 velocity = { 0, 0 };
	OwnMathFuncs::Vector2 drag = { 8, 8 };

	void update();

	~VelocityBody();
};

