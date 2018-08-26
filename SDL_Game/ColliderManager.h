#pragma once
#include "Collider.h"
#include <vector>


class ColliderManager
{
public:
	ColliderManager();
	~ColliderManager();

	void addCollider(Collider* collider);
	void update();

	std::vector<Collider*> isTrigger(Collider* collider_to_test);

private:
	std::vector<Collider*>* colliders_to_test = new std::vector<Collider*>();
	std::vector<Collider*> getIsTriggerColliders();
};

