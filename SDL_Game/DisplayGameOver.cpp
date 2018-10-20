#include "DisplayGameOver.h"
#include "Game.h"
#include "GameManager.h"

DisplayGameOver::DisplayGameOver(GameObject * gameObject) : Component(gameObject)
{
	titleGameOver = new Text(gameObject);
	titleGameOver->setCenter(true, true);
	titleGameOver->setPosition({ Game::instance()->getScreenSize().x / 2,
									Game::instance()->getScreenSize().y / 2 - 100 });
	titleGameOver->setText("YOU FINALLY DIED");
	titleGameOver->setFontSize(titleGameOverFontSize);
	titleGameOver->setLayer(RendererManager::MAX_LAYER);

	titleScore = new Text(gameObject);
	titleScore->setCenter(true, true);
	titleScore->setPosition({ Game::instance()->getScreenSize().x / 2,
								Game::instance()->getScreenSize().y / 2 - 40 });
	titleScore->setFontSize(titleScoreFontSize);
	titleScore->setLayer(RendererManager::MAX_LAYER);


	restartButton = new Button(gameObject);
	restartButton->setPosition({ Game::instance()->getScreenSize().x / 2,
									Game::instance()->getScreenSize().y / 2 + 120 });
	restartButton->getText()->setFontSize(titleScoreFontSize);
	restartButton->getText()->setLayer(RendererManager::MAX_LAYER);
	restartButton->getText()->setText("RESTART");
	restartButton->setSize({ 65, 12 });

	std::function<void()> restart = [this]() {restartLevel();};
	restartButton->setOnClickFunction(restart);


	mainMenuButton = new Button(gameObject);
	mainMenuButton->setPosition({ Game::instance()->getScreenSize().x / 2,
									Game::instance()->getScreenSize().y / 2 + 180 });
	mainMenuButton->getText()->setFontSize(titleScoreFontSize);
	mainMenuButton->getText()->setLayer(RendererManager::MAX_LAYER);
	mainMenuButton->getText()->setText("MAIN MENU");
	mainMenuButton->setSize({ 65, 12 });
}

DisplayGameOver::~DisplayGameOver()
{
}

void DisplayGameOver::start()
{

}

void DisplayGameOver::update()
{
	timeLeft -= Time::deltaTime;

	if (timeLeft <= 0) {

		if (!titleScore->isActive()) {
			titleScore->setActive(true);

			timeLeft = timeBeforeNextText;
		}
		else {
			restartButton->setActive(true);
			mainMenuButton->setActive(true);
		}
	}
}

void DisplayGameOver::transitionBetweenFloor(int playerGameScore)
{
	gameObject->active = true;

	std::string msg = "SOULS HARVESTED : " + std::to_string(playerGameScore) + "";
	titleScore->setText(msg);

	titleScore->setActive(false);

	restartButton->setActive(false);
	mainMenuButton->setActive(false);

	Game::instance()->getButtonManager()->setButtonSelected(restartButton);

	timeLeft = timeBeforeNextText;
}

void DisplayGameOver::restartLevel()
{
	gameObject->active = false;
	Game::instance()->findGameObject("Manager")->getComponent<GameManager>()->restartGame();
}
