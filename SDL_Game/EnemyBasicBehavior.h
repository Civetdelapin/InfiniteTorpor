#pragma once
#include "Component.h"
#include "VelocityBody.h"
#include "StateMachine.h"

class RoomBehavior;

class EnemyBasicBehavior : public Component
{
public:
	EnemyBasicBehavior(GameObject* gameObject);
	~EnemyBasicBehavior();

	void update();

	void addForce(OwnMathFuncs::Vector2 direction, float power , bool time_frame_dependent = true);
	bool takeDamage(OwnMathFuncs::Vector2 direction, float power_knock_back, float damage, float timeStunned);

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

	float getTimeBeforeEnemy();
	void setTimeBeforeEnemy(float value);

	void setRoomBehavior(RoomBehavior* roomBehavior);
	RoomBehavior* getRoomBehavior();

private:

	bool stunned = false;
	float currentHealthPoint;
	float maxHealthPoint = 100;
	float speed = 2300;

	float timeBeforeNextEnemy = 5.0f;

	RoomBehavior* roomBehavior;

	float knockBackResistance = 1;
	float timeStunned = 0;

	int scoreValue = 50;

	bool dying = false;

	void setDying();
};

