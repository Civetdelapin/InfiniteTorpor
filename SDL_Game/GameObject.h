#pragma once
#include "SDL.h"
#include <SDL_image.h>
#include "OwnMathFuncs.h"
#include <string>
#include <iostream>
#include "Time.h"
#include "TextureManager.h"
#include <vector>
#include <functional>

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


class Component;

// Base class for all the objects of the game
class GameObject
{

public:
	
	std::string tag = "Default";

	explicit GameObject(OwnMathFuncs::Vector2 init_local_pos = { 0, 0 });
	~GameObject();

	void update();
	void clean();

	void addComponent(Component* component);
	void addGameObjectAsChild(GameObject* gameObject);

	void setActiveChildren(bool value);

	std::vector<GameObject*> getChildren();
	std::vector<Component*> getAllComponents();

	GameObject* parentGameObject = nullptr;

	bool active = true;


	template< class ComponentType >
	ComponentType* getComponent() {
		for (auto && component : components) {

			if (ComponentType* t = dynamic_cast<ComponentType*>(component)) {
				return t;
			}	
		}

		return nullptr;
	}
	
	template< class ComponentType >
	std::vector<ComponentType*>  getComponents() {
		std::vector<ComponentType*> vec_temp;
		for (auto && component : components) {

			if (ComponentType* t = dynamic_cast<ComponentType*>(component)) {
				vec_temp.push_back(t);
			}
		}

		return vec_temp;
	}

	template< class ComponentType >
	ComponentType*  getComponentInChildren() {

		ComponentType* component = getComponent<ComponentType>();

		if (component != nullptr) {
			return component;
		}
		else {

			for (GameObject* gameObject : gameObjects) {
				component = gameObject->getComponent<ComponentType>();
				if (component != nullptr) {
					return component;
				}
				else {
					return gameObject->getComponentInChildren<ComponentType>();
				}

				component = NULL;
			}

		}

		return nullptr;
	}


	template< class ComponentType >
	ComponentType*  getComponentInParent() {

		if (parentGameObject == nullptr) {
			return getComponent<ComponentType>();
		}

		return parentGameObject->getComponentInParent<ComponentType>();
	}


	GameObject* getRootParent();

	OwnMathFuncs::Vector2 getWorldPosition();
	OwnMathFuncs::Vector2 getWorldScale();

	bool isReallyActive();

	OwnMathFuncs::Vector2 localPosition = { 0, 0 };
	OwnMathFuncs::Vector2 parentPosition = { 0, 0 };

	OwnMathFuncs::Vector2 localScale = { 1, 1 };
	OwnMathFuncs::Vector2 parentScale = { 1, 1 };

	OwnMathFuncs::Vector2 getStartPosition();

private:
	std::vector<Component*> components;
	std::vector<GameObject*> gameObjects;

	OwnMathFuncs::Vector2 startPosition = { 0, 0 };
};

#endif
