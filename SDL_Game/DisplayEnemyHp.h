#pragma once
#include "Renderer.h"
#include "EnemyBasicBehavior.h"

class DisplayEnemyHp : public Renderer
{
public:
	DisplayEnemyHp(GameObject* game_object, EnemyBasicBehavior* enemy_stat);
	~DisplayEnemyHp();

	void start();
	void update();
	void render();

	void clean();

	void setYOffset(float value);

private:
	EnemyBasicBehavior * enemy_stat;

	OwnMathFuncs::Vector2 size = { 23, 3 };
	float y_offset = 1.75;
	float time_display_when_hit = 3;

	float time_passed;
	float last_hp;
	float last_hp_display;
};

