#include "TransitionManager.h"



TransitionManager::TransitionManager(GameObject * gameObject) : Component(gameObject)
{

}

TransitionManager::~TransitionManager()
{

}

void TransitionManager::start()
{
}

void TransitionManager::update()
{
	if (timeLeft > 0) {
		timeLeft -= Time::deltaTime;

		if (timeLeft <= 0) {
			
			switch (state)
			{

			case TransitionManager::BetweenFloor:
				transitionBetweenFloor->transitionBetweenFloor(nextFloor);
				break;
			case TransitionManager::GameOver:
				_transitionGameOver->transitionBetweenFloor(playerScore);
				break;

			}

		}
	}
}

void TransitionManager::clean()
{
	Component::clean();
}

void TransitionManager::transitionBetweenFloors(int nextFloor)
{
	this->nextFloor = nextFloor;

	state = BetweenFloor;
	timeLeft = timeBeforeTransition;
}

void TransitionManager::transitionGameOver(int playerGameScore)
{
	this->playerScore = playerGameScore;

	state = GameOver;
	timeLeft = timeBeforeTransition;
}
