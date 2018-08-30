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

