#pragma once
#include "Component.h"
#include "DisplayBetweenFloor.h"

class TransitionManager : public Component
{
public:
	TransitionManager(GameObject* gameObject);
	~TransitionManager();

	DisplayBetweenFloor* transitionBetweenFloor;

	void start();
	void update();

	void clean();

	void transitionBetweenFloors(int nextFloor);

private :

	float timeLeft;
};

