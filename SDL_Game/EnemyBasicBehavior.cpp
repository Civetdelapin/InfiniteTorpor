#include "EnemyBasicBehavior.h"
#include "Game.h"

EnemyBasicBehavior::EnemyBasicBehavior(GameObject* game_object) : Component(game_object)
{
	cur_hp = max_hp;
}


EnemyBasicBehavior::~EnemyBasicBehavior()
{
}

void EnemyBasicBehavior::update()
{

	if (cur_hp > max_hp) {
		cur_hp = max_hp;
	}
	
	time_stunned -= Time::deltaTime;
	if (time_stunned <= 0) {
		is_stunned = false;
	}
}

void EnemyBasicBehavior::addForce(OwnMathFuncs::Vector2 direction, float power)
{
	if (!is_stunned) {
		OwnMathFuncs::OwnMathFuncs::normalize(direction);

		VelocityBody* velocity_body = game_object->getComponent<VelocityBody>();
		if (velocity_body != nullptr) {

			velocity_body->AddForce(direction, power * Time::deltaTime);

			//Manage the X scale according to the velocity
			if (velocity_body->getVelocity().x < 0 && game_object->getWorldScale().x > 0) {
				game_object->local_scale.x *= -1;
			}
			else if (velocity_body->getVelocity().x > 0 && game_object->getWorldScale().x < 0) {
				game_object->local_scale.x *= -1;
			}
		}

		velocity_body = NULL;
	}
}

void EnemyBasicBehavior::takeDamage(OwnMathFuncs::Vector2 direction, float power_knock_back, float damage, float time_stunned)
{
	cur_hp -= damage;
	if (cur_hp > 0) {
		VelocityBody* velocity_body = game_object->getComponent<VelocityBody>();
		if (velocity_body != nullptr) {
			velocity_body->AddForce(direction, power_knock_back * Time::deltaTime);
		}
		velocity_body = NULL;

		this->time_stunned = time_stunned;

		is_stunned = true;

		game_object->getComponent<StateMachine>()->play("Stun");
	}
	else if(!is_dying){
		setDying();
	}
}

bool EnemyBasicBehavior::isStunned()
{
	return is_stunned;
}

float EnemyBasicBehavior::getTimeStun()
{
	return time_stunned;
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
	return cur_hp;
}

void EnemyBasicBehavior::setMaxHP(float value)
{
	max_hp = value;
}

float EnemyBasicBehavior::getMaxHP()
{
	return max_hp;
}

void EnemyBasicBehavior::setDying()
{
	game_object->getRootParent()->getComponentInChild<StateMachine>()->play("Dying");

	is_dying = true;
}
