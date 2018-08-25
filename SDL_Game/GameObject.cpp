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
	//Update all ur components
	for (Component* component : components) {
		component->update();
	}

}

void GameObject::render(float camera_pos_x, float camera_pos_y)
{
	for (Component* component : components) {
		component->render(camera_pos_x, camera_pos_y);
	}
}

void GameObject::clean()
{
	for (Component* component : components) {
		component->clean();
	}

}


void GameObject::addComponent(Component * component)
{
	components.push_back(component);
}

template <class T>
void GameObject::removeComponent()
{
	int idFound = -1;
	for (int i = 0; i < components.size(); i++) {

		T *t = (T *)components[i];

		if (f != 0) {
			idFound = i;
			i = components.size();
		}
	}

	if (idFound >= 0) {
		vec.erase(vec.begin() + idFound);
	}
}


template <class T>
Component * GameObject::getComponent()
{
	
	for (Component* component : components) {

		T *t = (T *)component;

		if (f != 0) {
			return component;
		}

	}

	return nullptr;
}


