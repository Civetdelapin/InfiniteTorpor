#pragma once

#include "GameObject.h"
#include <string>
#include <functional>
#include <vector>
#include <memory>
#include <algorithm>

class Component
{
public:
	explicit Component(GameObject* game_object);
	~Component();

	virtual void update();
	virtual void render();
	virtual void clean();

	GameObject* game_object;


};

