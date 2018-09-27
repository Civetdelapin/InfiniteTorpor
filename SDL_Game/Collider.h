#pragma once
#include "Component.h"

class Game;

class Collider : public Component
{
public:
	Collider(GameObject* game_object);
	~Collider();

	virtual bool isColliding(Collider* collider) = 0;

	static bool AABB(SDL_Rect rectA, SDL_Rect rectB);

	bool isTrigger();
	void setIsTrigger(bool value);

	int getCollisionLayer();
	void setCollisionLayer(int value);

private:
	bool is_trigger = false;
	int collision_layer = 0;
};

