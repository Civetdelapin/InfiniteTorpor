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
	
	int layer = 0;

	std::string tag = "Default";

	explicit GameObject();
	~GameObject();

	virtual void handleEvents();
	virtual void update();
	virtual void render();
	void clean();

	void addComponent(Component* component);
	void addGameObject(GameObject* game_object);

	void setActiveChildren(bool value);

	std::vector<GameObject*> getChildren();
	std::vector<Component*> getAllComponents();

	GameObject* parent_game_object = nullptr;

	bool is_active = true;


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
	ComponentType*  getComponentInChild() {

		ComponentType* component = getComponent<ComponentType>();

		if (component != nullptr) {
			return component;
		}
		else {

			for (GameObject* game_object : game_objects) {
				component = game_object->getComponent<ComponentType>();
				if (component != nullptr) {
					return component;
				}

				component = NULL;
			}

		}

		return nullptr;
	}


	GameObject* getRootParent();

	OwnMathFuncs::Vector2 getWorldPosition();
	OwnMathFuncs::Vector2 getWorldScale();

	bool getIsReallyActive();

	OwnMathFuncs::Vector2 local_position = { 0, 0 };
	OwnMathFuncs::Vector2 parent_position = { 0, 0 };

	OwnMathFuncs::Vector2 local_scale = { 1, 1 };
	OwnMathFuncs::Vector2 parent_scale = { 1, 1 };

private:
	std::vector<Component*> components;
	std::vector<GameObject*> game_objects;
};

#endif
