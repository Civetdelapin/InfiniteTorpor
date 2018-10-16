#include "ColliderManager.h"



ColliderManager::ColliderManager()
{
}


ColliderManager::~ColliderManager()
{
}

void ColliderManager::addCollider(Collider* collider)
{
	collidersToTest.push_back(collider);
}

void ColliderManager::removeCollider(Collider * collider)
{
	collidersToTest.erase(std::remove(collidersToTest.begin(), collidersToTest.end(), collider), collidersToTest.end());
}

void ColliderManager::removeGameObjectColliders(GameObject * gameObject)
{
	std::vector<Collider*> vect = gameObject->getComponents<Collider>();
	for(Collider* collider : vect)
	{
		collidersToTest.erase(std::remove(collidersToTest.begin(), collidersToTest.end(), collider), collidersToTest.end());
	}

	for (GameObject* child : gameObject->getChildren()) {
		removeGameObjectColliders(child);
	}
}

void ColliderManager::update()
{
	
}

std::vector<Collider*> ColliderManager::isTrigger(Collider * collider_to_test)
{
	
	std::vector<Collider*> vecTemp;

	if (collider_to_test != nullptr) {
		if (collider_to_test->isReallyActive()) {

			for (Collider* collider : collidersToTest) {

				//std::cout << "TESTED COLLIDER" << std::endl;
				if (collider->isReallyActive() && collider->getCollisionLayer() == collider_to_test->getCollisionLayer() && collider->isActive() && !collider->isTrigger() && collider != collider_to_test && collider->isColliding(collider_to_test)) {
					vecTemp.push_back(collider);
				}
			}
		}
	}
	
	return vecTemp;
}

bool ColliderManager::isCollidingWithTag(Collider * collider_to_test, std::string tag)
{
	std::vector<Collider*> vect = isTrigger(collider_to_test);
	if (vect.size() > 0) {
		for (Collider* collider : vect) {
			if (collider->getGameObject()->tag == tag) {

				return true;

			}
		}
	}


	return false;
}

std::vector<Collider*> ColliderManager::getIsTriggerColliders()
{
	std::vector<Collider*> vecTemp;

	for (Collider* collider : collidersToTest) {
		
		if (collider->isTrigger()) {
			vecTemp.push_back(collider);
		}
		
	}

	return vecTemp;
}
