#pragma once
#include "Renderer.h"
#include "PlayerBehavior.h"
#include "Component.h"

class DisplayPlayerHealth : public Renderer, public Component
{
public:
	DisplayPlayerHealth(GameObject* gameObject);
	~DisplayPlayerHealth();

	void start();
	void update();
	void render();

	void clean();

private:
	SDL_Texture* fullHeartTexture;
	SDL_Texture* emptyHeartTexture;

	SDL_Rect sourceRect;
	
	PlayerBehavior* playerBehavior;
};

