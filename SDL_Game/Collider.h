#pragma once
#include "Renderer.h"

class Game;

class Collider : public Renderer
{
public:
	Collider(GameObject* game_object);
	~Collider();

	virtual bool isColliding(Collider* collider) = 0;

	static bool AABB(SDL_Rect rectA, SDL_Rect rectB);

	bool isTrigger();
	void setIsTrigger(bool value);

	void clean();

	int getCollisionLayer();
	void setCollisionLayer(int value);

private:
	bool is_trigger = false;
	int collision_layer = 0;
};

