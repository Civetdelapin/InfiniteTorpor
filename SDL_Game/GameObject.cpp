#include "GameObject.h"
#include "Component.h"

GameObject::GameObject()
{

}

GameObject::~GameObject()
{
}

void GameObject::handleEvents()
{

}

void GameObject::update()
{
	//Update all the components
	for (Component* component : components) {
		component->update();
	}

}

void GameObject::render(float camera_pos_x, float camera_pos_y)
{
	//Render all the components
	for (Component* component : components) {
		component->render(camera_pos_x, camera_pos_y);
	}
}

void GameObject::clean()
{
	//Clean all the components
	for (Component* component : components) {
		component->clean();
	}

}


void GameObject::addComponent(Component * component)
{
	components.push_back(component);
}






