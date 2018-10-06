#include "RendererManager.h"
#include "Game.h"
#include "Renderer.h"

RendererManager::RendererManager()
{
}


RendererManager::~RendererManager()
{
}

void RendererManager::addRenderer(Renderer * renderer)
{
	renderers_to_render.push_back(renderer);
}

void RendererManager::removeRenderer(Renderer * renderer)
{
	renderers_to_render.erase(std::remove(renderers_to_render.begin(), renderers_to_render.end(), renderer), renderers_to_render.end());
}

void RendererManager::render()
{
	SDL_SetRenderDrawColor(Game::instance()->renderer, 0, 0, 0, 255);
	SDL_RenderClear(Game::instance()->renderer);

	reorderRenderers();

	for (Renderer * my_renderer : renderers_to_render) {
		
		if (my_renderer->getComponent()->isReallyActive()) {
			my_renderer->render();
		}

	}

	SDL_RenderPresent(Game::instance()->renderer);
}

void RendererManager::reorderRenderers()
{
	
	std::sort(renderers_to_render.begin(), renderers_to_render.end(), [](Renderer* a, Renderer* b) {
		return a->getLayer() < b->getLayer();
	});

	std::sort(renderers_to_render.begin(), renderers_to_render.end(), [](Renderer* a, Renderer* b) {

		if (a->getLayer() == b->getLayer()) {

			return a->getBottomPosition().y < b->getBottomPosition().y;

		}

		return false;
	});
	
}
