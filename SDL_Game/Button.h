#pragma once
#include "Component.h"
#include "Text.h"
#include <functional>
#include "Renderer.h"

class Button : public Component, public Renderer
{
public:
	Button(GameObject* gameObject);
	~Button();

	Text* getText();

	void setActive(bool value);

	void setOnClickFunction(std::function<void()> f);

	void onClick();

	void update();
	void render();

	void clean();

	OwnMathFuncs::Vector2 getPosition();
	void setPosition(OwnMathFuncs::Vector2 value);
	void setSize(OwnMathFuncs::Vector2 value);

	void setBasicBackgroundColor(Color color);
	void setFocusBackgroundColor(Color color);

	void setFocus();
	void setBasic();

private:
	Text* buttonText;
	std::function<void()> onClickFunction;

	Color* currentColor;

	Color basicBackgroundColor = { 0, 0, 0, 0 };
	Color basicTextColor = { 255, 255, 255, 255 };

	Color focusBackgroundColor = { 255, 255, 255, 255 };
	Color focusTextColor = { 0, 0, 0, 255 };

	OwnMathFuncs::Vector2 position = { 0, 0 };
	OwnMathFuncs::Vector2 size = { 65, 15};

	SDL_Rect buttonRect;
};

