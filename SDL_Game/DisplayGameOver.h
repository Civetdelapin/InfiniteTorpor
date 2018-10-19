#pragma once
#include "Component.h"
#include "Text.h"
#include "Button.h"

class DisplayGameOver : public Component
{
public:
	DisplayGameOver(GameObject* gameObject);
	~DisplayGameOver();

	void start();
	void update();

	void transitionBetweenFloor(int playerGameScore);
	void restartLevel();

private:

	Text* titleGameOver;
	int titleGameOverFontSize = 40;

	Text* titleScore;
	int titleScoreFontSize = 40;

	Button* restartButton;
	Button* mainMenuButton;

	float timeBeforeNextText = 1;

	float timeLeft;
};

