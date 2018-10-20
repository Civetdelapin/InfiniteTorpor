#include "Rectangle.h"

Rectangle::Rectangle(GameObject* gameObject) : Component(gameObject), Renderer(this)
{

}


Rectangle::~Rectangle()
{
}

void Rectangle::update()
{
}

void Rectangle::render()
{
	rectangleRect.x = position.x - ((size.x / 2) * abs(gameObject->getWorldScale().x));
	rectangleRect.y = position.y - ((size.y / 2) * abs(gameObject->getWorldScale().y));

	rectangleRect.h = size.y * abs(gameObject->getWorldScale().y);
	rectangleRect.w = size.x * abs(gameObject->getWorldScale().x);

	TextureManager::DrawRect(rectangleRect, rectangleColor.r, rectangleColor.g, rectangleColor.b, rectangleColor.a, fill, false);
}

void Rectangle::clean()
{
	Renderer::clean();
	Component::clean();
}

void Rectangle::setPosition(OwnMathFuncs::Vector2 value)
{
	position = value;
}

void Rectangle::setSize(OwnMathFuncs::Vector2 value)
{
	size = value;
}

void Rectangle::setColor(Color value)
{
	rectangleColor = value;
}
