#include "DisplayBetweenFloor.h"
#include "TextureManager.h"
#include "Game.h"
#include "GameManager.h"

DisplayBetweenFloor::DisplayBetweenFloor(GameObject* gameObject) : Component(gameObject), Renderer(this)
{
	setLayer(RendererManager::MAX_LAYER);

	transitionSentences.push_back("The curse is still going strong...");
	transitionSentences.push_back("The drums in your head are louder and louder...");
	transitionSentences.push_back("Your thirst for blood is increasing...");
	transitionSentences.push_back("The end is near...");
	transitionSentences.push_back("Nobody can stop you now...");
}


DisplayBetweenFloor::~DisplayBetweenFloor()
{

}

void DisplayBetweenFloor::start()
{
	font = TTF_OpenFont("fonts/pixel.ttf", fontSize);
	font2 = TTF_OpenFont("fonts/pixel.ttf", font2Size);
}

void DisplayBetweenFloor::update()
{
	timeLeft -= Time::deltaTime;

	if (timeLeft <= 0) {
		if (!displayNextText) {
			displayNextText = true;
			timeLeft = timeBeforeNextText;
		}
		else {
			//Set the new floor
			gameObject->active = false;
			Game::instance()->findGameObject("Manager")->getComponent<GameManager>()->nextFloor();
		}
	}

}

void DisplayBetweenFloor::render()
{
	SDL_Rect destRect;
	destRect.y = Game::instance()->getScreenSize().y / 2 - 125;

	std::string floorMsg = "Floor n° -" + std::to_string(nextFloor) + "";
	TextureManager::DrawTextCenterScreen(font, destRect, floorMsg.c_str(), 255, 255, 255, 255, true, false);

	if (displayNextText) {
		destRect.y += 100;
		TextureManager::DrawTextCenterScreen(font2, destRect, currentSentence, 255, 255, 255, 255, true, false);
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

	currentSentence = transitionSentences[dist(rng)];
	//---------------
}
