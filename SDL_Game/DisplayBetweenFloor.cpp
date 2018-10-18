#include "DisplayBetweenFloor.h"
#include "TextureManager.h"
#include "Game.h"
#include "GameManager.h"

DisplayBetweenFloor::DisplayBetweenFloor(GameObject* gameObject) : Component(gameObject)
{
	
	transitionSentences.push_back("The curse is still going strong...");
	transitionSentences.push_back("The drums in your head are louder and louder...");
	transitionSentences.push_back("Your thirst for blood is increasing...");
	transitionSentences.push_back("The end is near...");
	transitionSentences.push_back("Nothing can stop you now...");
	transitionSentences.push_back("The rooms are all the same...");
	transitionSentences.push_back("There is no escape...");
	transitionSentences.push_back("You must kill everything...");
	transitionSentences.push_back("Why are you here ?...");
	transitionSentences.push_back("Dying is the only way out...");
	transitionSentences.push_back("You'd better give up...");
	transitionSentences.push_back("There is no point in fighting back...");
}


DisplayBetweenFloor::~DisplayBetweenFloor()
{

}

void DisplayBetweenFloor::start()
{

	SDL_Rect destRect;
	destRect.y = Game::instance()->getScreenSize().y / 2 - 125;
	destRect.x = Game::instance()->getScreenSize().x / 2;

	floorText = new Text(gameObject);
	floorText->setFontSize(floorTextfontSize);
	floorText->setCenter(true, false);
	floorText->setLayer(RendererManager::MAX_LAYER);
	floorText->setDestRect(destRect);

	sentenceText = new Text(gameObject);
	sentenceText->setFontSize(sentencefontSize);
	sentenceText->setActive(false);
	sentenceText->setCenter(true, false);
	sentenceText->setLayer(RendererManager::MAX_LAYER);
	destRect.y += 100;
	sentenceText->setDestRect(destRect);
}

void DisplayBetweenFloor::update()
{
	timeLeft -= Time::deltaTime;

	if (timeLeft <= 0) {
		if (!displayNextText) {
			displayNextText = true;
			sentenceText->setActive(true);

			timeLeft = timeBeforeNextText;
		}
		else {
			//Set the new floor
			gameObject->active = false;
			Game::instance()->findGameObject("Manager")->getComponent<GameManager>()->nextFloor();
		}
	}

	
}

void DisplayBetweenFloor::transitionBetweenFloor(int floor)
{
	nextFloor = floor;

	gameObject->active = true;
	displayNextText = false;

	timeLeft = timeBeforeNextText;

	//--- RANDOM THE SENTENCE ----
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> dist(0, transitionSentences.size() - 1);

	sentenceText->setText(transitionSentences[dist(rng)]);

	sentenceText->setActive(false);
	//---------------

	std::string floorMsg = "Floor n° -" + std::to_string(nextFloor) + "";
	floorText->setText(floorMsg);
}
