#include "GameManager.h"
#include "Game.h"
#include "MainMenu.h"

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

	uiManager->getComponent<TransitionManager>()->transitionBetweenFloors(gameObject->getComponent<GenerateLevel>()->getCurrentFloor() + 1);
}

void GameManager::restartGame()
{
	gameObject->getComponent<GenerateLevel>()->generateNewGame();

	if (player != nullptr) {

		PlayerBehavior* player_behavior = player->getComponent<PlayerBehavior>();
		if (player_behavior != nullptr) {
			player_behavior->restartGame();
		}
	}
}

void GameManager::startGame()
{
	
	if (mainMenu == nullptr) {
		mainMenu = Game::instance()->findGameObject("MainMenu");
	}
	mainMenu->active = false;

	if (mainGame == nullptr) {
		mainGame = Game::instance()->findGameObject("MainGameObject");
	}
	mainGame->active = true;

	gameObject->getRootParent()->active = true;
	gameObject->getComponent<GenerateLevel>()->generateNewGame();

	if (player != nullptr) {

		PlayerBehavior* player_behavior = player->getComponent<PlayerBehavior>();
		if (player_behavior != nullptr) {
			player_behavior->restartGame();
		}
	}
}

void GameManager::goMainMenu()
{
	mainMenu->active = true;
	mainGame->active = false;

	mainMenu->getComponent<MainMenu>()->activateMainMenu();

	gameObject->getComponent<GenerateLevel>()->cleanGeneratedData();
}

void GameManager::gameOver(int playerScore)
{
	if (uiManager != nullptr) {
		uiManager->getComponent<DisplayScreenFadeInOut>()->setState(DisplayScreenFadeInOut::FadingIn,
																		DisplayScreenFadeInOut::TIME_FADE_DEAD);
	}

	Game::instance()->getCamera()->setObjectToFollow(player);

	uiManager->getComponent<TransitionManager>()->transitionGameOver(playerScore);
}

void GameManager::nextFloor()
{
	gameObject->getComponent<GenerateLevel>()->playerNextFloor();
}

GameObject * GameManager::getMainGame()
{
	return mainGame;
}
