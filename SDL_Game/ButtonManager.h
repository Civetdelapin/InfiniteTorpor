#pragma once
#include <vector>

class Button;

class ButtonManager {

public:
	ButtonManager();
	~ButtonManager();

	void addButton(Button* button);
	void removeButton(Button* button);

	void update();

private:

	int currentIndex = 0;

	bool buttonOK = true;

	std::vector<Button*> buttons;

	void navigateButtons(bool goDown);
};

