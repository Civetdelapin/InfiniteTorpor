#include "ProjectileBehavior.h"
#include "Game.h"


ProjectileBehavior::ProjectileBehavior(GameObject* gameObject, float speed, Collider* hitboxCollider) : Component(gameObject), hitboxCollider(hitboxCollider), speed(speed)
{

}


ProjectileBehavior::~ProjectileBehavior()
{

}

void ProjectileBehavior::setDirection(OwnMathFuncs::Vector2 value)
{
	direction = OwnMathFuncs::OwnMathFuncs::getNormalize(value);
}

void ProjectileBehavior::setSpeed(float value)
{
	speed = value;
}

float ProjectileBehavior::getSpeed()
{
	return speed;
}

void ProjectileBehavior::update()
{
	

	//Collision detection and movement
	if (direction.x != 0) {
		float new_player_pos_x = gameObject->localPosition.x + direction.x * (speed * Time::deltaTime);

		//Save the old position in casse we need resolve collision
		float old_player_pos_x = gameObject->localPosition.x;

		gameObject->localPosition.x = new_player_pos_x;
		if (hitboxCollider != nullptr) {

			std::vector<Collider*> vect = Game::instance()->getColliderManager()->isTrigger(hitboxCollider);
			if (vect.size() > 0 && vect[0]->getGameObject()->tag != "Player") {
				gameObject->localPosition.x = old_player_pos_x;
				direction.x = 0;

				Game::instance()->destroyGameObject(gameObject);
			}
		}
	}

	if (direction.y != 0) {
		float new_player_pos_y = gameObject->localPosition.y + direction.y * (speed * Time::deltaTime);

		//Save the old position in casse we need resolve collision
		float old_player_pos_y = gameObject->localPosition.y;

		gameObject->localPosition.y = new_player_pos_y;
		if (hitboxCollider != nullptr) {

			std::vector<Collider*> vect = Game::instance()->getColliderManager()->isTrigger(hitboxCollider);
			if (vect.size() > 0 && vect[0]->getGameObject()->tag != "Player") {
				gameObject->localPosition.y = old_player_pos_y;
				direction.y = 0;

				Game::instance()->destroyGameObject(gameObject);
			}
		}
	}


}
