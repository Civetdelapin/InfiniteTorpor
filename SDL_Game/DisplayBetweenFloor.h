#pragma once
#include "Component.h"
#include "Text.h"

#include <random>

class DisplayBetweenFloor : public Component
{
public:
	DisplayBetweenFloor(GameObject * gameObject);
	~DisplayBetweenFloor();

	void start();
	void update();


	void transitionBetweenFloor(int floor);

private:

	Text * floorText;
	int floorTextfontSize = 40;

	Text * sentenceText;
	int sentencefontSize = 35;

	bool displayNextText = false;

	int nextFloor;

	std::vector<std::string> transitionSentences;

	float timeBeforeNextText = 2;
	float timeBeforeNextFloor = 5;

	float timeLeft;
};

