#pragma once
#include "Component.h"
class EnemyStat : public Component
{
public:
	EnemyStat(GameObject* game_object);
	~EnemyStat();

	float cur_hp;
	float max_hp = 100;

	void update();
};

