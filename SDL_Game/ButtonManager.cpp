#include "ButtonManager.h"
#include "Game.h"
#include "Button.h"

ButtonManager::ButtonManager()
{

}

ButtonManager::~ButtonManager()
{

}

void ButtonManager::addButton(Button * button)
{
	buttons.push_back(button);

	if (buttons.size() == 1) {
		button->setFocus();
	}

	std::sort(buttons.begin(), buttons.end(), [](Button* a, Button* b) {

		return a->getPosition().y > b->getPosition().y;
	});
}

void ButtonManager::removeButton(Button * button)
{
	buttons.erase(std::remove(buttons.begin(), buttons.end(), button), buttons.end());
}

void ButtonManager::update()
{
	if (buttons.size() > 0) {
		
		switch (Game::instance()->event.type) {
		case SDL_KEYUP:
			switch (Game::instance()->event.key.keysym.sym) {
				case SDLK_DOWN:
					buttonOK = true;
					break;
				case SDLK_UP:
					buttonOK = true;
					break;
				case SDLK_RETURN:
					buttonOK = true;
					break;
			}
			break;

		case SDL_KEYDOWN:
			
				switch (Game::instance()->event.key.keysym.sym) {
				
				case SDLK_DOWN:

					navigateButtons(true);
					break;
				case SDLK_UP:

					navigateButtons(false);
					break;

				case SDLK_RETURN:

					if(buttons[currentIndex]->isReallyActive() && buttonOK) {
						buttons[currentIndex]->onClick();
						buttonOK = false;
					}

					break;

				}
			break;

	
		}
		
	}
}

void ButtonManager::setButtonSelected(Button * button)
{
	ptrdiff_t pos = std::find(buttons.begin(), buttons.end(), button) - buttons.begin();
	if (pos < buttons.size() && pos != currentIndex) {

		buttons[currentIndex]->setBasic();
		buttons[pos]->setFocus();

		currentIndex = pos;
	}
}

void ButtonManager::navigateButtons(bool goDown)
{
	if (buttonOK) {
		
		int index = currentIndex;
		bool newButtonFound = false;

		do {

			index = goDown ? (index - 1) : (index + 1);

			if (index < 0) {
				index = buttons.size() - 1;
			}

			index = index % buttons.size();

			if (buttons[index]->isReallyActive() || currentIndex == index) {
				newButtonFound = true;
			}

		} while (!newButtonFound);

		buttons[currentIndex]->setBasic();
		buttons[index]->setFocus();

		currentIndex = index;

		buttonOK = false;
	}
}
