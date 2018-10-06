#include "Renderer.h"
#include "Game.h"

Renderer::Renderer(GameObject* game_object) : renderer_game_object(game_object)
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

GameObject * Renderer::getGameObjectRenderer()
{
	return renderer_game_object;
}

OwnMathFuncs::Vector2 Renderer::getBottomPosition()
{
	return renderer_game_object->getWorldPosition();
}
