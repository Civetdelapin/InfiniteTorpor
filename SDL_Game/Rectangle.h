#pragma once
#include "Component.h"
#include "Renderer.h"
#include "Color.h"

class Rectangle : public Component, public Renderer
{
public:
	Rectangle(GameObject* gameObject);
	~Rectangle();

	void update();
	void render();

	void clean();

	void setPosition(OwnMathFuncs::Vector2 value);
	void setSize(OwnMathFuncs::Vector2 value);
	void setColor(Color value);

private:
	SDL_Rect rectangleRect;
	Color rectangleColor;

	bool fill = true;

	OwnMathFuncs::Vector2 position = { 0, 0 };
	OwnMathFuncs::Vector2 size = { 65, 15 };
};



