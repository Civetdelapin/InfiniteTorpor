#pragma once
#include "Component.h"

class PlayerController;
class DisplayScreenFadeInOut;

class PlayerBehavior : public Component
{
public:
	PlayerBehavior(GameObject* gameObject);
	~PlayerBehavior();


	const enum State {spawning, playing};
	const int PLAYER_LAYER = 5;

	float getMaxHp();

	float getCurHP();
	bool addDamage(float dmg);

	int getScore();
	void addScore(int value);

	void start();
	void update();

	void setInvicible(float time);

	void startLevel();
	void endLevel();

private:

	float currentHealthPoint = 5;
	float maxHealthPoint = 5;

	float timeBeforeLoosingScore = 1.0f;
	float timeInvicible = 1.5f;
	float timeSpawn = 2.0f;

	int score = 0;

	bool invicible = false;
	bool dying = false;

	void setDying();

	State state = playing;

	float timeLeft;
	float timeLeftScore;
};

