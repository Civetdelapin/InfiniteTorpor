#include "Button.h"
#include "Game.h"

Button::Button(GameObject* gameObject) : Component(gameObject), Renderer(this)
{
	buttonText = new Text(gameObject);
	onClickFunction = []() { };

	buttonText->setCenter(true, true);
	setLayer(RendererManager::MAX_LAYER - 1);

	currentColor = &basicBackgroundColor;

	Game::instance()->getButtonManager()->addButton(this);
}

Button::~Button()
{

}

Text * Button::getText()
{
	return buttonText;
}

void Button::setActive(bool value)
{
	Component::setActive(value);
	buttonText->setActive(value);
}

void Button::setOnClickFunction(std::function<void()> function)
{
	onClickFunction = function;
}

void Button::onClick()
{
	onClickFunction();
}

void Button::update()
{
	buttonText->setPosition(position);
	buttonRect.x = position.x - ((size.x / 2) * abs(gameObject->getWorldScale().x));
	buttonRect.y = position.y - ((size.y / 2) * abs(gameObject->getWorldScale().y));

	buttonRect.h = size.y * abs(gameObject->getWorldScale().y);
	buttonRect.w = size.x * abs(gameObject->getWorldScale().x);

	if (false) {

		//We try to know if the mouse is on the button
		int mouseX, mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);
		bool mouseOnButton = mouseX > buttonRect.x && mouseX < (buttonRect.x + buttonRect.w) &&
			mouseY > buttonRect.y && mouseY < (buttonRect.y + buttonRect.h);

		//We update the colors
		if (mouseOnButton) {
			setFocus();
		}
		else {
			setBasic();
		}

		switch (Game::instance()->event.type) {
		case SDL_MOUSEBUTTONUP:
			if (mouseOnButton) {
				onClick();
			}
			break;
		}
	}

}

void Button::render()
{
	TextureManager::DrawRect(buttonRect, currentColor->r, currentColor->g, currentColor->b, currentColor->a, true, false);
}

void Button::clean()
{
	Game::instance()->getButtonManager()->removeButton(this);

	Renderer::clean();
	Component::clean();
}

OwnMathFuncs::Vector2 Button::getPosition()
{
	return position;
}

void Button::setPosition(OwnMathFuncs::Vector2 value)
{
	position = value;
}

void Button::setSize(OwnMathFuncs::Vector2 value)
{
	size = value;
}

void Button::setBasicBackgroundColor(Color color)
{
	
	basicBackgroundColor = color;
}

void Button::setFocusBackgroundColor(Color color)
{
	focusBackgroundColor = color;
}

void Button::setFocus()
{
	currentColor = &focusBackgroundColor;
	buttonText->setColor(focusTextColor);
}

void Button::setBasic()
{
	currentColor = &basicBackgroundColor;
	buttonText->setColor(basicTextColor);
}

