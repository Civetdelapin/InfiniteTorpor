#pragma once
#include "Component.h"

class Game;

class Collider : public Component
{
public:
	Collider(GameObject* game_object);
	~Collider();

	bool is_trigger = false;

	int collision_layer = 0;

	virtual bool isColliding(Collider* collider) = 0;

};

