#pragma once
#include "Component.h"
#include "Text.h"
#include "Button.h"
#include "Rectangle.h"

class DisplayGamePause : public Component
{
public:
	DisplayGamePause(GameObject* gameObject);
	~DisplayGamePause();

	void start();
	void update();

	void resume();
	void pause();

private:

	int fontSize = 40;

	SDL_Rect backgroundRect;
	Color backgroundColor;

	Button* resumeButton;
	Button* mainMenuButton;
};

