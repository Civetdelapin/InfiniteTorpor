#include "Text.h"



Text::Text(GameObject* gameObject) : Component(gameObject), Renderer(this)
{
}


Text::~Text()
{
}

void Text::setFontSize(float value)
{
	TTF_CloseFont(font);
	font = TTF_OpenFont("fonts/pixel.ttf", value);

	fontSize = value;
}

void Text::setText(std::string value)
{
	text = value;
}

void Text::start()
{
	font = TTF_OpenFont("fonts/pixel.ttf", fontSize);
}

void Text::update()
{

}

void Text::render()
{
	if (font != nullptr) {
		
		TextureManager::DrawText(font, destRect, text, color.r, color.g, color.b, color.a, relativeToCamera, centerX, centerY);
	}
}

void Text::clean()
{
	TTF_CloseFont(font);

	Renderer::clean();
	Component::clean();
}

void Text::setDestRect(SDL_Rect rect)
{
	destRect = rect;
}

void Text::setPosition(OwnMathFuncs::Vector2 vect)
{
	destRect.x = vect.x;
	destRect.y = vect.y;
}

void Text::setCenter(bool valueX, bool valueY)
{
	centerX = valueX;
	centerY = valueY;
}

void Text::setColor(int _r, int _g, int _b, int _a)
{
	color.r = _r;
	color.g = _g;
	color.b = _b;
	color.a = _a;
}

void Text::setColor(Color value)
{
	color = value;
}

void Text::setRelativeToCamera(bool value)
{
	relativeToCamera = value;
}
