#include "MainMenu.h"
#include "Game.h"
#include "GameManager.h"

MainMenu::MainMenu(GameObject* gameObject) : Component(gameObject)
{
	
	//------ FIRST SCREEN ----------
	firstScreen = new GameObject();

	Text* titleScreen = new Text(firstScreen);
	titleScreen->setText("INFINITE TORPOR");
	titleScreen->setCenter(true, true);
	titleScreen->setPosition({ Game::instance()->getScreenSize().x / 2,
		Game::instance()->getScreenSize().y / 2 - 300 });
	titleScreen->setFontSize(fontSizeTitle);
	titleScreen->setLayer(RendererManager::MAX_LAYER);
	
	resumeButton = new Button(firstScreen);
	resumeButton->setPosition({ Game::instance()->getScreenSize().x / 2,
		Game::instance()->getScreenSize().y / 2 - 100 });
	resumeButton->getText()->setFontSize(fontSizeButton);
	resumeButton->getText()->setLayer(RendererManager::MAX_LAYER);
	resumeButton->getText()->setText("PLAY");
	resumeButton->setSize({ 65, 12 });

	std::function<void()> play = [this]() {
		Game::instance()->findGameObject("Manager")->getComponent<GameManager>()->startGame();
	};
	resumeButton->setOnClickFunction(play);

	creditsButton = new Button(firstScreen);
	creditsButton->setPosition({ Game::instance()->getScreenSize().x / 2,
		Game::instance()->getScreenSize().y / 2 });
	creditsButton->getText()->setFontSize(fontSizeButton);
	creditsButton->getText()->setLayer(RendererManager::MAX_LAYER);
	creditsButton->getText()->setText("CREDITS");
	creditsButton->setSize({ 65, 12 });

	std::function<void()> toCredits = [this]() {
		firstScreen->active = false; 
		creditsScreen->active = true; 
		Game::instance()->getButtonManager()->setButtonSelected(backButton);
	};
	creditsButton->setOnClickFunction(toCredits);
	
	Button* quitButton = new Button(firstScreen);
	quitButton->setPosition({ Game::instance()->getScreenSize().x / 2,
		Game::instance()->getScreenSize().y / 2 + 100 });
	quitButton->getText()->setFontSize(fontSizeButton);
	quitButton->getText()->setLayer(RendererManager::MAX_LAYER);
	quitButton->getText()->setText("QUIT");
	quitButton->setSize({ 65, 12 });
	std::function<void()> quitGame = [this]() {

		Game::instance()->quitGame();
	};
	quitButton->setOnClickFunction(quitGame);
	//---------------------------------------

	//------- CREDITS SCREEN ----------------
	creditsScreen = new GameObject();

	Text* programmer = new Text(creditsScreen);
	programmer->setText("PROGRAMMER : BAPTISTE \"CIVETDELAPIN\" REY");
	programmer->setCenter(true, true);
	programmer->setPosition({ Game::instance()->getScreenSize().x / 2,
		Game::instance()->getScreenSize().y / 2 - 300 });
	programmer->setFontSize(fontSizeTitle);
	programmer->setLayer(RendererManager::MAX_LAYER);


	backButton = new Button(creditsScreen);
	backButton->setPosition({ Game::instance()->getScreenSize().x / 2,
		Game::instance()->getScreenSize().y / 2 + 100 });
	backButton->getText()->setFontSize(fontSizeButton);
	backButton->getText()->setLayer(RendererManager::MAX_LAYER);
	backButton->getText()->setText("BACK");
	backButton->setSize({ 65, 12 });

	std::function<void()> toFirst = [this]() {
		firstScreen->active = true;
		creditsScreen->active = false;
		Game::instance()->getButtonManager()->setButtonSelected(creditsButton);
	};
	backButton->setOnClickFunction(toFirst);
	//--------------------------------------

	gameObject->addGameObjectAsChild(firstScreen);
	gameObject->addGameObjectAsChild(creditsScreen);
}


MainMenu::~MainMenu()
{

}

void MainMenu::start()
{
	activateMainMenu();
}

void MainMenu::activateMainMenu()
{
	gameObject->active = true;
	firstScreen->active = true;
	creditsScreen->active = false;

	Game::instance()->getButtonManager()->setButtonSelected(resumeButton);
}
