#pragma once
#include "Component.h"
#include "VelocityBody.h"
#include "StateMachine.h"

class EnemyBasicBehavior : public Component
{
public:
	EnemyBasicBehavior(GameObject* game_object);
	~EnemyBasicBehavior();

	void update();

	void addForce(OwnMathFuncs::Vector2 direction, float power);
	bool takeDamage(OwnMathFuncs::Vector2 direction, float power_knock_back, float damage, float time_stunned);

	bool isStunned();
	float getTimeStun();

	void setSpeed(float value);
	float getSpeed();

	float getCurHP();

	void setScoreValue(int value);
	int getScoreValue();

	void setMaxHP(float value);
	float getMaxHP();

	void setKnockBackResistance(float value);

private:

	bool is_stunned = false;
	float cur_hp;
	float max_hp = 100;
	float speed = 2300;

	float knock_back_resistance = 1;

	float time_stunned = 0;

	int score_value = 50;

	bool is_dying = false;

	void setDying();
};

