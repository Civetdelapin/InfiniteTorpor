#pragma once
#include "Component.h"
#include "Player.h"
#include "PlayerBehavior.h"
#include "DisplayScreenFadeInOut.h"
#include "GenerateLevel.h"
#include "TransitionManager.h"

class GameManager : public Component
{
public:
	GameManager(GameObject* gameObject);
	~GameManager();

	void start();
	void update();

	void clean();

	void startLevel(OwnMathFuncs::Vector2 position);
	void endLevel();
	void restartGame();

	void gameOver(int playerScore);
	void nextFloor();

private:

	GameObject* player;
	GameObject* uiManager;
};

