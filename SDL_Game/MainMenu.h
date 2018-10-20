#pragma once
#include "Component.h"
#include "Text.h"
#include "Button.h"

class MainMenu : public Component
{
public:
	MainMenu(GameObject* gameObject);
	~MainMenu();

	void start();
	void activateMainMenu();

private:

	GameObject * firstScreen;

	Button* resumeButton;
	Button* creditsButton;


	GameObject* creditsScreen;

	Button* backButton;

	int fontSizeTitle = 55;
	int fontSizeButton = 40;
};

