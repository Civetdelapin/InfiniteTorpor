#pragma once
#include "Component.h"
#include "Renderer.h"
#include "Color.h"

class Text : public Component, public Renderer
{
public:
	Text(GameObject* gameObject);
	~Text();

	void setFontSize(float value);
	void setText(std::string value);

	void start();
	void update();
	void render();

	void clean();

	void setDestRect(SDL_Rect rect);
	void setPosition(OwnMathFuncs::Vector2 vect);
	void setCenter(bool valueX, bool valueY);
	void setColor(int _r, int _g, int _b, int _a);
	void setColor(Color color);
	void setRelativeToCamera(bool value);

private:
	float fontSize = 5;
	TTF_Font * font;

	std::string text = "";

	bool centerX = false;
	bool centerY = false;

	bool relativeToCamera = false;

	Color color;
	SDL_Rect destRect;
};

