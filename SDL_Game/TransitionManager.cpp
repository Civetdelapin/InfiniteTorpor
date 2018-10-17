#include "TransitionManager.h"



TransitionManager::TransitionManager(GameObject * gameObject) : Component(gameObject)
{

}

TransitionManager::~TransitionManager()
{

}

void TransitionManager::start()
{
}

void TransitionManager::update()
{

}

void TransitionManager::clean()
{
	Component::clean();
}

void TransitionManager::transitionBetweenFloors(int nextFloor)
{
	transitionBetweenFloor->transitionBetweenFloor(nextFloor);
}
