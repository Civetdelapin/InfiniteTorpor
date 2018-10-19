#include "DisplayBetweenFloor.h"
#include "TextureManager.h"
#include "Game.h"
#include "GameManager.h"

DisplayBetweenFloor::DisplayBetweenFloor(GameObject* gameObject) : Component(gameObject)
{
	
	transitionSentences.push_back("THE CURSE IS STILL GOING STRONG...");
	transitionSentences.push_back("THE DRUMS IN YOUR HEAD ARE LOUDER AND LOUDER...");
	transitionSentences.push_back("YOUR THIRST FOR BLOOD IS INCREASING...");
	transitionSentences.push_back("THE END IS NEAR...");
	transitionSentences.push_back("NOTHING CAN STOP YOU NOW...");
	transitionSentences.push_back("THE ROOMS ARE ALL THE SAME...");
	transitionSentences.push_back("THERE IS NO ESPACE...");
	transitionSentences.push_back("YOU MUST KILL EVERYTHING...");
	transitionSentences.push_back("WHY ARE YOU HERE ?...");
	transitionSentences.push_back("DYING IS THE ONLY WAY OUT...");
	transitionSentences.push_back("YOU'D BETTER GIVE UP...");
	transitionSentences.push_back("THERE IS NO POINT IN FIGHTING BACK...");
	

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


DisplayBetweenFloor::~DisplayBetweenFloor()
{

}

void DisplayBetweenFloor::start()
{

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

	std::string floorMsg = "FLOOR n° -" + std::to_string(nextFloor) + "";
	floorText->setText(floorMsg);
}
