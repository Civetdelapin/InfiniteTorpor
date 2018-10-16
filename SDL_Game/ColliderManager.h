#pragma once
#include "Collider.h"
#include <vector>


class ColliderManager
{
public:
	ColliderManager();
	~ColliderManager();

	void addCollider(Collider* collider);
	void removeCollider(Collider* collider);
	void removeGameObjectColliders(GameObject* gameObject);

	void update();

	std::vector<Collider*> isTrigger(Collider* collider_to_test);

	bool isCollidingWithTag(Collider* collider_to_test, std::string tag);

private:
	std::vector<Collider*> collidersToTest;
	std::vector<Collider*> getIsTriggerColliders();
};

