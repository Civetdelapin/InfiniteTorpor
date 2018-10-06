#include "Renderer.h"
#include "Game.h"

Renderer::Renderer(Component* component) : component(component)
{
	Game::instance()->getRendererManager()->addRenderer(this);
}

Renderer::~Renderer()
{

}

void Renderer::clean()
{
	Game::instance()->getRendererManager()->removeRenderer(this);
}

void Renderer::setLayer(int value)
{
	layer = value;
}

int Renderer::getLayer()
{
	return layer;
}

Component * Renderer::getComponent()
{
	return component;
}

OwnMathFuncs::Vector2 Renderer::getBottomPosition()
{
	return component->getGameObject()->getWorldPosition();
}
