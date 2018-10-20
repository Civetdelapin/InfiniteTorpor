#pragma once
#include "GameObject.h"
#include <vector>

class Scene
{
public:
	Scene();
	~Scene();



private:

	std::vector<GameObject*> gameObjects;

};

