#include "DisplayPlayerScore.h"
#include "Game.h"


DisplayPlayerScore::DisplayPlayerScore(GameObject* gameObject) : Renderer(this), Component(gameObject)
{

	setLayer(RendererManager::MAX_LAYER - 2);
}


DisplayPlayerScore::~DisplayPlayerScore()
{

}


void DisplayPlayerScore::start()
{
	ttf_Font = TTF_OpenFont("fonts/pixel.ttf", fontSize);

	GameObject* player = Game::instance()->findGameObject("Player");
	if (player != nullptr) {
		playerBehavior = player->getComponent<PlayerBehavior>();
	}
}

void DisplayPlayerScore::update()
{

	
}


void DisplayPlayerScore::render()
{
	if (playerBehavior != nullptr) {

		SDL_Rect destRect;
		destRect.y = 70;
		destRect.x = 20;

		std::string msg = "SOULS : " + std::to_string(playerBehavior->getScore());

		TextureManager::DrawText(ttf_Font, destRect, msg, 255, 255, 255, 255, false);
	}
}

void DisplayPlayerScore::clean()
{
	TTF_CloseFont(ttf_Font);

	Renderer::clean();
	Component::clean();
}
