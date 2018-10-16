#pragma once
#include "Component.h"

class PlayerController;
class DisplayScreenFadeInOut;

class PlayerBehavior : public Component
{
public:
	PlayerBehavior(GameObject* game_object);
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

	float cur_hp = 5;
	float max_hp = 5;

	float time_loose_score = 1.0f;
	float time_invicible = 1.5f;
	float time_spawn = 2.0f;

	int score = 0;

	bool is_invicible = false;
	bool is_dying = false;

	void setDying();

	State state = playing;

	float timeLeft;
	float timeLeft_score;
};

