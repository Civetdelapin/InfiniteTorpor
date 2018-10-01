#pragma once
#include "GameObject.h"
#include "Component.h"


class Renderer : public Component
{
public:
	Renderer(GameObject* game_object);
	~Renderer();

	virtual void render() = 0;
	void clean();

	void setLayer(int value);
	int getLayer();

	virtual OwnMathFuncs::Vector2 getBottomPosition();

private:
	int layer;
};

