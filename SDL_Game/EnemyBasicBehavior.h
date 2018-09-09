#pragma once
#include "Component.h"
#include "VelocityBody.h"
class EnemyBasicBehavior : public Component
{
public:
	EnemyBasicBehavior(GameObject* game_object);
	~EnemyBasicBehavior();

	float cur_hp;
	float max_hp = 100;

	float speed = 2300;

	void update();

	void addForce(OwnMathFuncs::Vector2 direction, float power);
	void takeDamage(OwnMathFuncs::Vector2 direction, float power_knock_back, float damage, float time_stunned);

	bool isStunned();

private:

	bool is_stunned = false;
	float time_stunned = 0;
};

