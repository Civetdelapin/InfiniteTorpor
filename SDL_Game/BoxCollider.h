#pragma once
#include "Collider.h"
class BoxCollider : public Collider
{
public:
	BoxCollider(GameObject* game_object);
	~BoxCollider();

	bool isColliding(Collider* collider);

	OwnMathFuncs::Vector2 size = { 10, 10};
	OwnMathFuncs::Vector2 offset = { 0, 0 };

	SDL_Rect rect;

	void update();
	void render(float camera_pos_x, float camera_pos_y);
};

