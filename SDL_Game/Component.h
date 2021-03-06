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
	explicit Component(GameObject* gameObject);
	virtual ~Component();

	virtual void start();
	virtual void update();

	virtual void clean();

	bool isReallyActive();

	virtual void setActive(bool value);
	bool isActive();

	void setHasStart(bool value);
	bool getHasStart();


	GameObject * getGameObject();

protected:
	GameObject * gameObject;
	bool active = true;
	bool hasStart = false;
};

