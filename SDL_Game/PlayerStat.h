#pragma once
#include "Component.h"
#include "PlayerController.h"

class PlayerStat : public Component
{
public:
	PlayerStat(GameObject* game_object);
	~PlayerStat();

	float cur_hp = 100;
	float max_hp = 100;

	void update();
};

