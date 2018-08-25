#pragma once

#include "GameObject.h"

class Component
{
public:
	explicit Component(GameObject* game_object);
	~Component();

	virtual void update();

protected:

	GameObject* game_object;

};

