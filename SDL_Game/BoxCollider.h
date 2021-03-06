#pragma once
#include "Collider.h"

class BoxCollider : public Collider
{
public:
	BoxCollider(GameObject* gameObject, bool is_in_simulation = true);
	~BoxCollider();

	bool isColliding(Collider* collider);

	OwnMathFuncs::Vector2 size = { 10, 10};
	OwnMathFuncs::Vector2 offset = { 0, 0 };

	SDL_Rect getRect();
	
	void start();
	void update();
	void render();

	OwnMathFuncs::Vector2 getWorldPosition();

private:
	SDL_Rect rect;
};

