#pragma once
#include "Component.h"
#include "EnemyBasicBehavior.h"

class DisplayEnemyHp : public Component
{
public:
	DisplayEnemyHp(GameObject* game_object, EnemyBasicBehavior* enemy_stat);
	~DisplayEnemyHp();

	void update();
	void render();

	OwnMathFuncs::Vector2 size = {23, 3};
		 
	float y_offset = 1.75;

	float time_display_when_hit = 3;

private:
	EnemyBasicBehavior * enemy_stat;

	float time_passed;
	float last_hp;


	float last_hp_display;
};

