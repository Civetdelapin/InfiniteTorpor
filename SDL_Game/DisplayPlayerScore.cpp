#include "DisplayPlayerScore.h"



DisplayPlayerScore::DisplayPlayerScore(GameObject* game_object, PlayerStat* player_stat) : Renderer(this), Component(game_object), player_stat(player_stat)
{

}


DisplayPlayerScore::~DisplayPlayerScore()
{

}


void DisplayPlayerScore::start()
{
	ttf_font = TTF_OpenFont("fonts/pixel.ttf", font_size);
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

	TextureManager::DrawText(ttf_font, dest_rect, msg, 255, 255, 255, 255, false);
}

void DisplayPlayerScore::clean()
{
	TTF_CloseFont(ttf_font);

	Renderer::clean();
	Component::clean();
}
