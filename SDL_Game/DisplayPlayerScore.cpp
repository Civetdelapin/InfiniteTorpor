#include "DisplayPlayerScore.h"



DisplayPlayerScore::DisplayPlayerScore(GameObject* game_object, PlayerStat* player_stat) : Renderer(game_object), player_stat(player_stat)
{
}


DisplayPlayerScore::~DisplayPlayerScore()
{

}


void DisplayPlayerScore::start()
{

}

void DisplayPlayerScore::update()
{

	
}


void DisplayPlayerScore::render()
{
	SDL_Rect dest_rect;
	dest_rect.y = 70;
	dest_rect.x = 20;

	std::string msg = "Score : " + std::to_string(player_stat->getScore());

	TextureManager::DrawText(dest_rect, msg, font_size, 255, 255, 255, 255, false);
}
