#include "Renderer.h"
#include "Game.h"

Renderer::Renderer(GameObject * game_object) : Component(game_object)
{
	Game::instance()->getRendererManager()->addRenderer(this);
}

Renderer::~Renderer()
{

}

void Renderer::clean()
{
	Game::instance()->getRendererManager()->removeRenderer(this);
	Component::clean();
}

void Renderer::setLayer(int value)
{
	layer = value;
}

int Renderer::getLayer()
{
	return layer;
}

OwnMathFuncs::Vector2 Renderer::getBottomPosition()
{
	return getGameObject()->getWorldPosition();
}
