#include "Component.h"

Component::Component(GameObject* gameObject) : gameObject(gameObject)
{
	gameObject->addComponent(this);
}


Component::~Component()
{

}

void Component::start()
{
}

void Component::update()
{
}


void Component::clean()
{
	gameObject = NULL;
}

bool Component::isReallyActive()
{
	if (active) {
		return gameObject->isReallyActive();
	}

	return false;
}

void Component::setActive(bool value)
{
	active = value;
}

bool Component::isActive()
{
	return active;
}

void Component::setHasStart(bool value)
{
	hasStart = value;
}

bool Component::getHasStart()
{
	return hasStart;
}

GameObject * Component::getGameObject()
{
	return gameObject;
}

