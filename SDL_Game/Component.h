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
	virtual void render(float camera_pos_x, float camera_pos_y);
	virtual void clean();

	GameObject* game_object;


};

