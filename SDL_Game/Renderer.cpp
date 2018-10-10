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
	if (value > RendererManager::MAX_LAYER) {
		value = RendererManager::MAX_LAYER;
	}
	else if (value < RendererManager::MIN_LAYER) {
		value = RendererManager::MIN_LAYER;
	}

	Game::instance()->getRendererManager()->modifyLayer(this, value);
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
