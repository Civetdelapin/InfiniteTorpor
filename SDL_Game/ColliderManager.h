#pragma once
#include "Collider.h"
#include <vector>


class ColliderManager
{
public:
	ColliderManager();
	~ColliderManager();

	void addCollider(Collider* collider);
	void removeGameObjectColliders(GameObject* game_object);

	void update();

	std::vector<Collider*> isTrigger(Collider* collider_to_test);

private:
	std::vector<Collider*> colliders_to_test;
	std::vector<Collider*> getIsTriggerColliders();
};

