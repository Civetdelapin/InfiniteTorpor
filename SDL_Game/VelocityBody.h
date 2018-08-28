#pragma once
#include "Component.h"

class VelocityBody : public Component
{
public:
	VelocityBody(GameObject* game_object);

	OwnMathFuncs::Vector2 velocity = { 0, 0 };
	OwnMathFuncs::Vector2 drag = { 20, 20};

	void update();

	~VelocityBody();
};

