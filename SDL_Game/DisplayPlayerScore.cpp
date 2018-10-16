#include "DisplayPlayerScore.h"
#include "Game.h"


DisplayPlayerScore::DisplayPlayerScore(GameObject* game_object) : Renderer(this), Component(game_object)
{

	setLayer(RendererManager::MAX_LAYER - 2);
}


DisplayPlayerScore::~DisplayPlayerScore()
{

}


void DisplayPlayerScore::start()
{
	ttf_font = TTF_OpenFont("fonts/pixel.ttf", font_size);

	GameObject* player = Game::instance()->findGameObject("Player");
	if (player != nullptr) {
		player_stat = player->getComponent<PlayerBehavior>();
	}
}

void DisplayPlayerScore::update()
{

	
}


void DisplayPlayerScore::render()
{
	if (player_stat != nullptr) {

		SDL_Rect dest_rect;
		dest_rect.y = 70;
		dest_rect.x = 20;

		std::string msg = "Score : " + std::to_string(player_stat->getScore());

		TextureManager::DrawText(ttf_font, dest_rect, msg, 255, 255, 255, 255, false);
	}
}

void DisplayPlayerScore::clean()
{
	TTF_CloseFont(ttf_font);

	Renderer::clean();
	Component::clean();
}
