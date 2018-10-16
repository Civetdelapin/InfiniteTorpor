#pragma once
#include "Renderer.h"
#include "PlayerBehavior.h"
#include "Component.h"

class DisplayPlayerHealth : public Renderer, public Component
{
public:
	DisplayPlayerHealth(GameObject* game_object);
	~DisplayPlayerHealth();

	void start();
	void update();
	void render();

	void clean();

private:
	SDL_Texture* full_heart_texture;
	SDL_Texture* empty_heart_texture;

	SDL_Rect src_rect;
	
	PlayerBehavior* player_stat;
};

