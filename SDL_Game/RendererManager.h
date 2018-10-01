#pragma once
#include <vector>

class Renderer;

class RendererManager
{
public:
	RendererManager();
	~RendererManager();

	void addRenderer(Renderer* renderer);
	void removeRenderer(Renderer* renderer);

	void render();

private:
	std::vector<Renderer*> renderers_to_render;

	void reorderRenderers();
};

