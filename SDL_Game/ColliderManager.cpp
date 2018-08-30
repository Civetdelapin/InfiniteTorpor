#include "ColliderManager.h"



ColliderManager::ColliderManager()
{
}


ColliderManager::~ColliderManager()
{
}

void ColliderManager::addCollider(Collider* collider)
{
	colliders_to_test.push_back(collider);
}

void ColliderManager::removeGameObjectColliders(GameObject * game_object)
{
	std::vector<Collider*> vect = game_object->getComponents<Collider>();
	for(Collider* collider : vect)
	{
		colliders_to_test.erase(std::remove(colliders_to_test.begin(), colliders_to_test.end(), collider), colliders_to_test.end());
	}

	for (GameObject* child : game_object->getChildren()) {
		removeGameObjectColliders(child);
	}
}

void ColliderManager::update()
{
	//std::vector<Collider*> colliders_is_trigger = getIsTriggerColliders();
}

std::vector<Collider*> ColliderManager::isTrigger(Collider * collider_to_test)
{
	//std::cout << "--------------------------" << std::endl;
	std::vector<Collider*> vecTemp;

	if (collider_to_test->game_object->getIsReallyActive()){

		for (Collider* collider : colliders_to_test) {

			//std::cout << "TESTED COLLIDER" << std::endl;
			if (collider->game_object->getIsReallyActive() && collider->collision_layer == collider_to_test->collision_layer && collider->is_active &&!collider->is_trigger && collider != collider_to_test && collider->isColliding(collider_to_test)) {
				vecTemp.push_back(collider);
			}
		}
	}

	return vecTemp;
}

std::vector<Collider*> ColliderManager::getIsTriggerColliders()
{
	std::vector<Collider*> vecTemp;

	for (Collider* collider : colliders_to_test) {

		if (collider->is_trigger) {
			vecTemp.push_back(collider);
		}

	}

	return vecTemp;
}
