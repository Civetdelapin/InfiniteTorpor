#pragma once
#include "Component.h"
#include "Renderer.h"

class Game;

class Collider : public Renderer, public Component
{
public:
	Collider(GameObject* gameObject, bool is_in_simulation = true);
	virtual ~Collider();

	virtual bool isColliding(Collider* collider) = 0;

	bool isTrigger();
	void setIsTrigger(bool value);

	virtual void clean();

	int getCollisionLayer();
	void setCollisionLayer(int value);

	virtual OwnMathFuncs::Vector2 getWorldPosition();

private:
	bool trigger = false;
	int collisionLayer = 0;
};

