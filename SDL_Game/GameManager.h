#pragma once
#include "Component.h"
#include "Player.h"
#include "PlayerBehavior.h"
#include "DisplayScreenFadeInOut.h"
#include "GenerateLevel.h"

class GameManager : public Component
{
public:
	GameManager(GameObject* game_object);
	~GameManager();

	void start();
	void update();

	void clean();

	void startLevel(OwnMathFuncs::Vector2 position);
	void endLevel();

private:
	GameObject* player;
	GameObject* uiManager;

	float timeLeft;
};

