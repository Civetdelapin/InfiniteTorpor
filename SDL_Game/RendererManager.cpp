#include "RendererManager.h"
#include "Game.h"
#include "Renderer.h"

RendererManager::RendererManager()
{
	for (int i = MIN_LAYER; i <= MAX_LAYER; i++) {
		std::vector<Renderer*> vect;
		renderers_to_render.push_back(vect);
	}

}


RendererManager::~RendererManager()
{
}

void RendererManager::addRenderer(Renderer * renderer)
{
	renderers_to_render[renderer->getLayer()].push_back(renderer);
}

void RendererManager::removeRenderer(Renderer * renderer)
{
	renderers_to_render[renderer->getLayer()].erase(std::remove(renderers_to_render[renderer->getLayer()].begin(), renderers_to_render[renderer->getLayer()].end(), renderer), renderers_to_render[renderer->getLayer()].end());
}

void RendererManager::modifyLayer(Renderer * renderer, int new_layer)
{
	renderers_to_render[renderer->getLayer()].erase(std::remove(renderers_to_render[renderer->getLayer()].begin(), renderers_to_render[renderer->getLayer()].end(), renderer), renderers_to_render[renderer->getLayer()].end());

	renderers_to_render[new_layer].push_back(renderer);
}

void RendererManager::render()
{
	SDL_SetRenderDrawColor(Game::instance()->renderer, 0, 0, 0, 255);
	SDL_RenderClear(Game::instance()->renderer);

	int i = 0;
	for (std::vector<Renderer*> renderer_vect : renderers_to_render) {

		if (i == TOP_DOWN_LAYER) {
			reorderRenderers(i);
		}
		
		for (Renderer * my_renderer : renderer_vect) {

			if (my_renderer->getComponent()->isReallyActive()) {
				my_renderer->render();
			}

		}

		i++;
	}
	
	SDL_RenderPresent(Game::instance()->renderer);
}

void RendererManager::reorderRenderers(int index)
{
	
	std::sort(renderers_to_render[index].begin(), renderers_to_render[index].end(), [](Renderer* a, Renderer* b) {
		
		return a->getBottomPosition().y < b->getBottomPosition().y;
	});
	
}
