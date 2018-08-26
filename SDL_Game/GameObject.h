#pragma once
#include "SDL.h"
#include <SDL_image.h>
#include "OwnMathFuncs.h"
#include <string>
#include <iostream>
#include "Time.h"
#include "TextureManager.h"
#include <vector>

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class Component;

// Base class for all the objects of the game
class GameObject
{

public:
	
	OwnMathFuncs::Vector2 position = {0, 0};
	OwnMathFuncs::Vector2 scale = { 1, 1};

	int layer = 0;

	explicit GameObject();
	~GameObject();

	virtual void handleEvents();
	virtual void update();
	virtual void render(float camera_pos_x, float camera_pos_y);
	void clean();

	void addComponent(Component* component);

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

	template <class T>
	T* getComponent()
	{

		for (Component* component : components) {

			T *t = (T *)component;

			if (t != 0) {
				return t;
			}

		}

		return nullptr;
	}

private:
	std::vector<Component*> components;
};

#endif
