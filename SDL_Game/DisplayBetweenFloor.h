#pragma once
#include "Component.h"
#include "Renderer.h"
#include <random>

class DisplayBetweenFloor : public Component, Renderer
{
public:
	DisplayBetweenFloor(GameObject * gameObject);
	~DisplayBetweenFloor();

	void start();
	void update();

	void render();

	void transitionBetweenFloor(int floor);

private:

	TTF_Font * font;
	int fontSize = 40;

	TTF_Font * font2;
	int font2Size = 35;

	bool displayNextText = false;

	int nextFloor;

	std::string currentSentence;

	std::vector<std::string> transitionSentences;

	float timeBeforeNextText = 2;
	float timeBeforeNextFloor = 5;

	float timeLeft;
};

