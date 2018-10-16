#include "DisplayPlayerHealth.h"
#include "Game.h"


DisplayPlayerHealth::DisplayPlayerHealth(GameObject* gameObject) : Renderer(this), Component(gameObject)
{
	sourceRect.x = 0;
	sourceRect.y = 0;

	fullHeartTexture = TextureManager::LoadTexture("img/ui/heart_full.png", sourceRect.w, sourceRect.h);
	emptyHeartTexture = TextureManager::LoadTexture("img/ui/heart_empty.png");

	setLayer(RendererManager::MAX_LAYER - 2);
}


DisplayPlayerHealth::~DisplayPlayerHealth()
{

}

void DisplayPlayerHealth::start()
{
	GameObject* player = Game::instance()->findGameObject("Player");
	if (player != nullptr) {
		playerBehavior = player->getComponent<PlayerBehavior>();
	}
}

void DisplayPlayerHealth::update()
{
	
}

void DisplayPlayerHealth::render()
{
	if (playerBehavior != nullptr) {

		SDL_Rect destRect;
		destRect.w = sourceRect.w * 0.25;
		destRect.h = sourceRect.h * 0.25;
		destRect.y = 15;
		destRect.x = 15;

		//std::cout << playerBehavior->currentHealthPoint << std::endl;
		int maxHealthPoint = playerBehavior->getMaxHp();
		for (int i = 1; i <= maxHealthPoint; i++) {

			if (i <= playerBehavior->getCurHP()) {
				TextureManager::DrawTexture(fullHeartTexture, sourceRect, destRect, SDL_FLIP_NONE, false);
			}
			else {
				TextureManager::DrawTexture(emptyHeartTexture, sourceRect, destRect, SDL_FLIP_NONE, false);
			}

			destRect.x += (destRect.w + 15);
		}
	}
}

void DisplayPlayerHealth::clean()
{
	SDL_DestroyTexture(fullHeartTexture);
	fullHeartTexture = NULL;

	SDL_DestroyTexture(emptyHeartTexture);
	emptyHeartTexture = NULL;

	playerBehavior = NULL;

	Renderer::clean();
	Component::clean();
}
