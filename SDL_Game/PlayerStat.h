#pragma once
#include "Component.h"

class PlayerController;
class DisplayScreenFadeInOut;

class PlayerStat : public Component
{
public:
	PlayerStat(GameObject* game_object);
	~PlayerStat();


	float getMaxHp();

	float getCurHP();
	bool addDamage(float dmg);

	int getScore();
	void addScore(int value);

	void start();
	void update();

	void setInvicible(float time);

private:

	float cur_hp = 5;
	float max_hp = 5;

	float time_loose_score = 1.0f;

	float time_invicible = 1.5f;

	int score = 0;

	bool is_invicible = false;

	bool is_dying = false;

	void setDying();

	float time_passed;
	float time_passed_score;
};

