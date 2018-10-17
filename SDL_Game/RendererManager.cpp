#include "RendererManager.h"
#include "Game.h"
#include "Renderer.h"

RendererManager::RendererManager()
{
	for (int i = MIN_LAYER; i <= MAX_LAYER; i++) {
		std::vector<Renderer*> vect;
		renderersToRender.push_back(vect);
	}

}


RendererManager::~RendererManager()
{
}

void RendererManager::addRenderer(Renderer * renderer)
{
	renderersToRender[renderer->getLayer()].push_back(renderer);
}

void RendererManager::removeRenderer(Renderer * renderer)
{
	renderersToRender[renderer->getLayer()].erase(std::remove(renderersToRender[renderer->getLayer()].begin(), renderersToRender[renderer->getLayer()].end(), renderer), renderersToRender[renderer->getLayer()].end());
}

void RendererManager::modifyLayer(Renderer * renderer, int new_layer)
{
	renderersToRender[renderer->getLayer()].erase(std::remove(renderersToRender[renderer->getLayer()].begin(), renderersToRender[renderer->getLayer()].end(), renderer), renderersToRender[renderer->getLayer()].end());

	renderersToRender[new_layer].push_back(renderer);
}

void RendererManager::render()
{
	SDL_SetRenderDrawColor(Game::instance()->getRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(Game::instance()->getRenderer());

	int i = 0;
	for (std::vector<Renderer*> renderer_vect : renderersToRender) {

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
	
	SDL_RenderPresent(Game::instance()->getRenderer());
}

void RendererManager::reorderRenderers(int index)
{
	
	std::sort(renderersToRender[index].begin(), renderersToRender[index].end(), [](Renderer* a, Renderer* b) {
		
		return a->getBottomPosition().y < b->getBottomPosition().y;
	});
	
}
