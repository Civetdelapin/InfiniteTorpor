#include "DisplayGamePause.h"
#include "Game.h"

DisplayGamePause::DisplayGamePause(GameObject * gameObject) : Component(gameObject)
{
	Rectangle* rectangle = new Rectangle(gameObject);
	rectangle->setLayer(RendererManager::MAX_LAYER - 2);
	rectangle->setSize({ 85, 60 });
	rectangle->setPosition({ Game::instance()->getScreenSize().x / 2,
		Game::instance()->getScreenSize().y / 2 + 40});
	rectangle->setColor({ 0, 0, 0, 255 });


	Text* titleText = new Text(gameObject);
	titleText->setLayer(RendererManager::MAX_LAYER);
	titleText->setText("GAME PAUSED");
	titleText->setFontSize(fontSize);
	titleText->setPosition({ Game::instance()->getScreenSize().x / 2, 
								Game::instance()->getScreenSize().y / 2 - 20 });
	titleText->setCenter(true, true);


	resumeButton = new Button(gameObject);
	resumeButton->setPosition({ Game::instance()->getScreenSize().x / 2,
		Game::instance()->getScreenSize().y / 2 + 40 });
	resumeButton->getText()->setFontSize(fontSize);
	resumeButton->getText()->setLayer(RendererManager::MAX_LAYER);
	resumeButton->getText()->setText("RESUME");
	resumeButton->setSize({ 65, 12 });

	std::function<void()> restart = [this]() {resume();};
	resumeButton->setOnClickFunction(restart);

	mainMenuButton = new Button(gameObject);
	mainMenuButton->setPosition({ Game::instance()->getScreenSize().x / 2,
		Game::instance()->getScreenSize().y / 2 + 100 });
	mainMenuButton->getText()->setFontSize(fontSize);
	mainMenuButton->getText()->setLayer(RendererManager::MAX_LAYER);
	mainMenuButton->getText()->setText("MAIN MENU");
	mainMenuButton->setSize({ 65, 12 });
}

DisplayGamePause::~DisplayGamePause()
{

}

void DisplayGamePause::start()
{
}

void DisplayGamePause::update()
{

}


void DisplayGamePause::resume()
{
	gameObject->active = false;
	Time::timeScale = 1;
}

void DisplayGamePause::pause()
{
	if (!gameObject->active) {
		gameObject->active = true;
		Time::timeScale = 0;

		Game::instance()->getButtonManager()->setButtonSelected(resumeButton);
	}
}
