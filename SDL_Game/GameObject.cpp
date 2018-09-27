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
		if (component->is_active) {
			component->update();
		}
	}


	for (GameObject* game_object : game_objects) {
		game_object->parent_position = getWorldPosition();
		game_object->parent_scale = getWorldScale();

		if (game_object->is_active) {
			game_object->update();
		}
	}
}

void GameObject::render()
{
	//Render all the components
	for (Component* component : components) {
		if (component->is_active) {
			component->render();
		}
	}

	for (GameObject* game_object : game_objects) {
		if (game_object->is_active) {
			game_object->render();
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

	for (GameObject* game_object : getChildren()) {
		game_object->clean();

		delete game_object;
	}

	getChildren().clear();
}


void GameObject::addComponent(Component * component)
{
	components.push_back(component);
}

void GameObject::addGameObject(GameObject * game_object)
{
	game_object->parent_game_object = this;
	game_objects.push_back(game_object);
}

void GameObject::setActiveChildren(bool value)
{
	for (GameObject* game_object : game_objects) {
		game_object->is_active = value;
		game_object->setActiveChildren(value);
	}
}

std::vector<GameObject*> GameObject::getChildren()
{
	return game_objects;
}

std::vector<Component*> GameObject::getAllComponents()
{
	return components;
}



GameObject * GameObject::getRootParent()
{
	
	if (parent_game_object == nullptr) {
		return this;
	}
	else {
		return parent_game_object->getRootParent();
	}

}

OwnMathFuncs::Vector2 GameObject::getWorldPosition()
{
	return local_position + parent_position;
}

OwnMathFuncs::Vector2 GameObject::getWorldScale()
{
	OwnMathFuncs::Vector2 vect = { local_scale.x * parent_scale.x, local_scale.y * parent_scale.y };
	return vect;
}

bool GameObject::getIsReallyActive()
{
	if (parent_game_object == nullptr || is_active == false) {
		return is_active;
	}
	else {
		return parent_game_object->getIsReallyActive();
	}
}

