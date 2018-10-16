#include "GameObject.h"
#include "Component.h"


GameObject::GameObject(OwnMathFuncs::Vector2 init_local_pos) : localPosition(init_local_pos), startPosition(init_local_pos)
{
	
}

GameObject::~GameObject()
{
}


void GameObject::update()
{
	//Update all the components
	for (Component* component : components) {

		if (component->isActive()) {

			if (!component->getHasStart()) {
				component->start();

				component->setHasStart(true);
			}

			component->update();
		}
	}


	for (GameObject* gameObject : gameObjects) {
		gameObject->parentPosition = getWorldPosition();
		gameObject->parentScale = getWorldScale();

		if (gameObject->active) {
			gameObject->update();
		}
	}
}

void GameObject::clean()
{
	//Clean all the components
	for (Component* component : getAllComponents()) {
		component->clean();

		delete component;
	}

	getAllComponents().clear();

	for (GameObject* gameObject : getChildren()) {
		gameObject->clean();

		delete gameObject;
	}

	getChildren().clear();
}


void GameObject::addComponent(Component * component)
{
	components.push_back(component);
}

void GameObject::addGameObjectAsChild(GameObject * gameObject)
{
	gameObject->parentGameObject = this;
	gameObjects.push_back(gameObject);
}

void GameObject::setActiveChildren(bool value)
{
	for (GameObject* gameObject : gameObjects) {
		gameObject->active = value;
		gameObject->setActiveChildren(value);
	}
}

std::vector<GameObject*> GameObject::getChildren()
{
	return gameObjects;
}

std::vector<Component*> GameObject::getAllComponents()
{
	return components;
}



GameObject * GameObject::getRootParent()
{
	
	if (parentGameObject == nullptr) {
		return this;
	}
	else {
		return parentGameObject->getRootParent();
	}

}

OwnMathFuncs::Vector2 GameObject::getWorldPosition()
{
	return (localPosition * parentScale) + parentPosition;
}

OwnMathFuncs::Vector2 GameObject::getWorldScale()
{
	OwnMathFuncs::Vector2 vect = { localScale.x * parentScale.x, localScale.y * parentScale.y };
	return vect;
}

bool GameObject::isReallyActive()
{
	if (parentGameObject == nullptr || active == false) {
		return active;
	}
	else {
		return parentGameObject->isReallyActive();
	}
}

OwnMathFuncs::Vector2 GameObject::getStartPosition()
{
	return startPosition;
}

