#include "Component.h"



Component::Component(GameObject* game_object) : game_object(game_object)
{
	game_object->addComponent(this);
}


Component::~Component()
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

