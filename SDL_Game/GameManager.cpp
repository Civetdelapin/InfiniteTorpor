#include "GameManager.h"
#include "Game.h"


GameManager::GameManager(GameObject * gameObject) : Component(gameObject)
{

}

GameManager::~GameManager()
{
}

void GameManager::start()
{
	
}

void GameManager::update()
{
	
	if (timeLeft > 0) {
		timeLeft -= Time::deltaTime;

		if (timeLeft <= 0) {
			if (uiManager != nullptr) {
				uiManager->getComponent<TransitionManager>()->transitionBetweenFloors(gameObject->getComponent<GenerateLevel>()->getCurrentFloor() + 1);
			}
		}
	}

}

void GameManager::clean()
{
}

void GameManager::startLevel(OwnMathFuncs::Vector2 position)
{
	if (player == nullptr) {
		player = Game::instance()->findGameObject("Player");
	}

	if (player != nullptr) {
		player->localPosition = position;

		PlayerBehavior* player_behavior = player->getComponent<PlayerBehavior>();
		if (player_behavior != nullptr) {
			player_behavior->startLevel();
		}

		Game::instance()->getCamera()->setCameraPos(position);
		Game::instance()->getCamera()->setObjectToFollow(player);
	}

	if (uiManager == nullptr) {
		uiManager = Game::instance()->findGameObject("UI_Manager");
	}

	if (uiManager != nullptr) {
		uiManager->getComponent<DisplayScreenFadeInOut>()->setState(DisplayScreenFadeInOut::FadingOut, DisplayScreenFadeInOut::TIME_FADE_TRANSITION);
	}
}

void GameManager::endLevel()
{

	if (uiManager != nullptr) {
		uiManager->getComponent<DisplayScreenFadeInOut>()->setState(DisplayScreenFadeInOut::FadingIn, DisplayScreenFadeInOut::TIME_FADE_TRANSITION);
	}

	if (player != nullptr) {

		PlayerBehavior* player_behavior = player->getComponent<PlayerBehavior>();
		if (player_behavior != nullptr) {
			player_behavior->endLevel();
		}
	}

	timeLeft = timeBeforeTransition;
}

void GameManager::nextFloor()
{
	gameObject->getComponent<GenerateLevel>()->playerNextFloor();
}
