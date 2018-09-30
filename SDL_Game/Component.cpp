#include "Component.h"



Component::Component(GameObject* game_object) : game_object(game_object)
{
	game_object->addComponent(this);
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

void Component::render()
{
}


void Component::clean()
{
	game_object = NULL;
}

bool Component::getIsReallyActive()
{
	if (is_active) {
		return game_object->getIsReallyActive();
	}
	else {
		return is_active;
	}
}

void Component::setIsActive(bool value)
{
	is_active = value;
}

bool Component::isActive()
{
	return is_active;
}

void Component::setHasStart(bool value)
{
	has_start = value;
}

bool Component::getHasStart()
{
	return has_start;
}

GameObject * Component::getGameObject()
{
	return game_object;
}

