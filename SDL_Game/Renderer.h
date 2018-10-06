#pragma once
#include "GameObject.h"
#include "Component.h"


class Renderer
{
public:
	Renderer(GameObject* game_object);
	virtual ~Renderer();

	virtual void render() = 0;
	void clean();

	void setLayer(int value);
	int getLayer();

	GameObject* getGameObjectRenderer();

	virtual OwnMathFuncs::Vector2 getBottomPosition();

private:
	int layer;
	GameObject* renderer_game_object;
};

