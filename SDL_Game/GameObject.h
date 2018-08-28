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

	explicit GameObject();
	~GameObject();

	virtual void handleEvents();
	virtual void update();
	virtual void render();
	void clean();

	void addComponent(Component* component);
	void addGameObject(GameObject* game_object);

	bool is_active = true;

	//NOT WORKING NEED REDO
	/*
	template <class T>
	void removeComponent()
	{
		int idFound = -1;
		for (int i = 0; i < components.size(); i++) {

			T *t = (T *)components[i];

			if (t != 0) {
				idFound = i;
				i = components.size();
			}
		}

		if (idFound >= 0) {
			vec.erase(vec.begin() + idFound);
		}
	}
	*/

	template< class ComponentType >
	ComponentType* getComponent() {
		for (auto && component : components) {

			if (ComponentType* t = dynamic_cast<ComponentType*>(component)) {

				return t;
			}	
		}

		return nullptr;
	}
	
	OwnMathFuncs::Vector2 getWorldPosition();
	OwnMathFuncs::Vector2 getWorldScale();

	OwnMathFuncs::Vector2 local_position = { 0, 0 };
	OwnMathFuncs::Vector2 parent_position = { 0, 0 };

	OwnMathFuncs::Vector2 local_scale = { 1, 1 };
	OwnMathFuncs::Vector2 parent_scale = { 1, 1 };

private:
	std::vector<Component*> components;
	std::vector<GameObject*> game_objects;
	
};

#endif
