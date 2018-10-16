#pragma once
#include "Renderer.h"
#include "EnemyBasicBehavior.h"
#include "Component.h"

class DisplayEnemyHp : public Renderer, public Component
{
public:
	DisplayEnemyHp(GameObject* gameObject, EnemyBasicBehavior* enemyBehavior);
	~DisplayEnemyHp();

	void start();
	void update();
	void render();

	void clean();

	void setYOffset(float value);

private:
	EnemyBasicBehavior * enemyBehavior;

	OwnMathFuncs::Vector2 size = { 23, 3 };
	float Yoffset = 1.75;
	float timeToDisplayWhenHit = 3;

	float timeLeft;
	float lastHP;
	float lastHpDisplay;
};

