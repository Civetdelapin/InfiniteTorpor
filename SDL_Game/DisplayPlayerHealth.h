#pragma once
#include "Component.h"
#include "PlayerStat.h"

class DisplayPlayerHealth : public Component
{
public:
	DisplayPlayerHealth(GameObject* game_object, PlayerStat* player_stat);
	~DisplayPlayerHealth();

	void update();
	void render();
	void clean();

private:
	SDL_Texture* full_heart_texture;
	SDL_Texture* empty_heart_texture;

	SDL_Rect src_rect;
	
	PlayerStat* player_stat;
};

