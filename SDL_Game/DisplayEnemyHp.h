#pragma once
#include "Component.h"
#include "EnemyStat.h"

class DisplayEnemyHp : public Component
{
public:
	DisplayEnemyHp(GameObject* game_object, EnemyStat* enemy_stat);
	~DisplayEnemyHp();

	void update();
	void render();

	OwnMathFuncs::Vector2 size = {23, 3};
		 
	float time_display_when_hit = 3;

private:
	EnemyStat * enemy_stat;

	float time_passed;
	float last_hp;


	float last_hp_display;
};

