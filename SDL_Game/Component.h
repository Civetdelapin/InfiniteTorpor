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

	virtual void start();
	virtual void update();

	virtual void clean();

	bool isReallyActive();

	void setIsActive(bool value);
	bool isActive();

	void setHasStart(bool value);
	bool getHasStart();


	GameObject * getGameObject();

protected:
	GameObject * game_object;
	bool is_active = true;
	bool has_start = false;
};

