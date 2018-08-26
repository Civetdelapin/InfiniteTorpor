#include "ColliderManager.h"



ColliderManager::ColliderManager()
{
}


ColliderManager::~ColliderManager()
{
}

void ColliderManager::addCollider(Collider* collider)
{
	colliders_to_test->push_back(collider);
}

void ColliderManager::update()
{
	std::vector<Collider*> colliders_is_trigger = getIsTriggerColliders();


}

std::vector<Collider*> ColliderManager::isTrigger(Collider * collider_to_test)
{
	//std::cout << "--------------------------" << std::endl;

	std::vector<Collider*> vecTemp;
	for (Collider* collider : *colliders_to_test) {

		//std::cout << "TESTED COLLIDER" << std::endl;

		if (collider->collision_layer == collider_to_test->collision_layer  && !collider->is_trigger && collider != collider_to_test && collider_to_test->isColliding(collider)) {

			vecTemp.push_back(collider);
		}

	}

	return vecTemp;
}

std::vector<Collider*> ColliderManager::getIsTriggerColliders()
{
	std::vector<Collider*> vecTemp;

	for (Collider* collider : *colliders_to_test) {

		if (collider->is_trigger) {
			vecTemp.push_back(collider);
		}

	}

	return vecTemp;
}
