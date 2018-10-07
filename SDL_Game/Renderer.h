#pragma once
#include "Component.h"


class Renderer
{
public:
	Renderer(Component* component);
	virtual ~Renderer();

	virtual void render() = 0;
	void clean();

	void setLayer(int value);
	int getLayer();

	Component* getComponent();

	virtual OwnMathFuncs::Vector2 getBottomPosition();

private:
	int layer;
	Component* component;
};

