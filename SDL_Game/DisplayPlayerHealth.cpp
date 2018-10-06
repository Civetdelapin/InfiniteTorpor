#include "DisplayPlayerHealth.h"



DisplayPlayerHealth::DisplayPlayerHealth(GameObject* game_object, PlayerStat* player_stat) : Renderer(game_object), Component(game_object), player_stat(player_stat)
{
	src_rect.x = 0;
	src_rect.y = 0;

	full_heart_texture = TextureManager::LoadTexture("img/ui/heart_full.png", src_rect.w, src_rect.h);
	empty_heart_texture = TextureManager::LoadTexture("img/ui/heart_empty.png");

}


DisplayPlayerHealth::~DisplayPlayerHealth()
{

}

void DisplayPlayerHealth::start()
{
}

void DisplayPlayerHealth::update()
{
	
}

void DisplayPlayerHealth::render()
{
	SDL_Rect dest_rect;
	dest_rect.w = src_rect.w * 0.25;
	dest_rect.h = src_rect.h * 0.25;
	dest_rect.y = 15;
	dest_rect.x = 15;

	//std::cout << player_stat->cur_hp << std::endl;
	for (int i = 1; i <= player_stat->max_hp; i++) {
		
		if (i <= player_stat->getCurHP()) {
			TextureManager::DrawTexture(full_heart_texture, src_rect, dest_rect, SDL_FLIP_NONE, false);
		}
		else {
			TextureManager::DrawTexture(empty_heart_texture, src_rect, dest_rect, SDL_FLIP_NONE, false);
		}

		dest_rect.x += (dest_rect.w + 15);
	}
	
}

void DisplayPlayerHealth::clean()
{
	SDL_DestroyTexture(full_heart_texture);
	full_heart_texture = NULL;

	SDL_DestroyTexture(empty_heart_texture);
	empty_heart_texture = NULL;

	player_stat = NULL;

	Renderer::clean();
	Component::clean();
}
