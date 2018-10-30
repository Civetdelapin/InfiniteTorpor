#include "EnemyBasicBehavior.h"
#include "Game.h"
#include "RoomBehavior.h"

EnemyBasicBehavior::EnemyBasicBehavior(GameObject* gameObject) : Component(gameObject)
{
	currentHealthPoint = maxHealthPoint;
}


EnemyBasicBehavior::~EnemyBasicBehavior()
{
}

void EnemyBasicBehavior::update()
{

	if (currentHealthPoint > maxHealthPoint) {
		currentHealthPoint = maxHealthPoint;
	}
	
	timeStunned -= Time::deltaTime;
	if (timeStunned <= 0) {
		stunned = false;
	}
}

void EnemyBasicBehavior::addForce(OwnMathFuncs::Vector2 direction, float power, bool time_frame_dependent)
{
	if (!stunned) {
		OwnMathFuncs::OwnMathFuncs::normalize(direction);

		VelocityBody* velocityBody = gameObject->getComponent<VelocityBody>();
		if (velocityBody != nullptr) {

			if (time_frame_dependent) {
				velocityBody->AddForce(direction, power * Time::deltaTime);
			}
			else {
				velocityBody->AddForce(direction, power);
			}
			

			//Manage the X scale according to the velocity
			if (velocityBody->getVelocity().x < 0 && gameObject->getWorldScale().x > 0) {
				gameObject->localScale.x *= -1;
			}
			else if (velocityBody->getVelocity().x > 0 && gameObject->getWorldScale().x < 0) {
				gameObject->localScale.x *= -1;
			}
		}

		velocityBody = NULL;
	}
}

int EnemyBasicBehavior::takeDamage(OwnMathFuncs::Vector2 direction, float power_knock_back, float damage, float timeStunned)
{
	currentHealthPoint -= damage;
	if (currentHealthPoint > 0) {
		VelocityBody* velocityBody = gameObject->getComponent<VelocityBody>();
		if (velocityBody != nullptr) {
			velocityBody->AddForce(direction, knockBackResistance * power_knock_back);
		}
		velocityBody = NULL;

		if (knockBackResistance > 0) {
			this->timeStunned = timeStunned * knockBackResistance;
			stunned = true;
			gameObject->getComponent<StateMachine>()->play("Stun");
		}

		return 0;
	}
	else if(!dying){
		setDying();

		return 2;
	}

	return 1;
}

bool EnemyBasicBehavior::isStunned()
{
	return stunned;
}

float EnemyBasicBehavior::getTimeStun()
{
	return timeStunned;
}

void EnemyBasicBehavior::setSpeed(float value)
{
	speed = value;
}

float EnemyBasicBehavior::getSpeed()
{
	return speed;
}

float EnemyBasicBehavior::getCurHP()
{
	return currentHealthPoint;
}

void EnemyBasicBehavior::setScoreValue(int value)
{
	scoreValue = value;
}

int EnemyBasicBehavior::getScoreValue()
{
	return scoreValue;
}

void EnemyBasicBehavior::setMaxHP(float value)
{
	currentHealthPoint = value;
	maxHealthPoint = value;
}

float EnemyBasicBehavior::getMaxHP()
{
	return maxHealthPoint;
}

void EnemyBasicBehavior::setKnockBackResistance(float value)
{
	knockBackResistance = value;
}

float EnemyBasicBehavior::getTimeBeforeEnemy()
{
	return timeBeforeNextEnemy;
}

void EnemyBasicBehavior::setTimeBeforeEnemy(float value)
{
	timeBeforeNextEnemy = value;
}

void EnemyBasicBehavior::setRoomBehavior(RoomBehavior * roomBehavior)
{
	this->roomBehavior = roomBehavior;
}

RoomBehavior * EnemyBasicBehavior::getRoomBehavior()
{
	return roomBehavior;
}

void EnemyBasicBehavior::setDying()
{
	gameObject->getRootParent()->getComponentInChildren<StateMachine>()->play("Dying");

	dying = true;
}
