#pragma once
#include "Component.h"
#include "DisplayBetweenFloor.h"
#include "DisplayGameOver.h"

class TransitionManager : public Component
{
public:
	TransitionManager(GameObject* gameObject);
	~TransitionManager();

	DisplayBetweenFloor* transitionBetweenFloor;
	DisplayGameOver* _transitionGameOver;

	void start();
	void update();

	void clean();

	void transitionBetweenFloors(int nextFloor);
	void transitionGameOver(int playerGameScore);

	const enum State { Over, BetweenFloor, GameOver };

private :

	float timeBeforeTransition = 2;
	float timeLeft;

	int nextFloor;
	int playerScore;

	State state;
};

