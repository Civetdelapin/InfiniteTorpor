#pragma once
#include "Component.h"
#include "PlayerController.h"

class PlayerStat : public Component
{
public:
	PlayerStat(GameObject* game_object);
	~PlayerStat();

	const float max_hp = 5;
	const float time_invicible = 2;
	
	float getCurHP();
	void addDamage(float dmg);

	void update();

	void setInvicible(float time);

private:

	float cur_hp = 5;
	bool is_invicible = false;

	float time_passed;
};

