#include "VelocityBody.h"
#include "Game.h"

VelocityBody::VelocityBody(GameObject* gameObject) : Component(gameObject)
{

	collider = gameObject->getComponent<Collider>();

}

float clip(float n, float lower, float upper) {
	return std::max(lower, std::min(n, upper));
}


void VelocityBody::update()
{
	//Make the drag
	velocity.x = velocity.x * clip(1 - Time::deltaTime * drag.x, 0, 1);
	if (fabs(velocity.x) < 0.1)
		velocity.x = 0.0f;

	velocity.y = velocity.y * clip(1 - Time::deltaTime * drag.x, 0, 1);
	if (fabs(velocity.y) < 0.1)
		velocity.y = 0.0f;

	//Collision detection
	if (velocity.x != 0) {
		float new_player_pos_x = gameObject->localPosition.x + (velocity.x * Time::deltaTime);

		//Save the old position in casse we need resolve collision
		float old_player_pos_x = gameObject->localPosition.x;

		gameObject->localPosition.x = new_player_pos_x;
		if (collider != nullptr) {

			std::vector<Collider*> vect = Game::instance()->getColliderManager()->isTrigger(collider);
			if (vect.size() > 0) {
				gameObject->localPosition.x = old_player_pos_x;
				velocity.x = 0;
			}
		}
	}

	if (velocity.y != 0) {
		float new_player_pos_y = gameObject->localPosition.y + (velocity.y * Time::deltaTime);

		//Save the old position in casse we need resolve collision
		float old_player_pos_y = gameObject->localPosition.y;

		gameObject->localPosition.y = new_player_pos_y;
		if (collider != nullptr) {

			std::vector<Collider*> vect = Game::instance()->getColliderManager()->isTrigger(collider);
			if (vect.size() > 0) {
				gameObject->localPosition.y = old_player_pos_y;
				velocity.y = 0;
			}
		}
	}


}

void VelocityBody::setVelocity(OwnMathFuncs::Vector2 value)
{
	velocity = value;
}

OwnMathFuncs::Vector2 VelocityBody::getVelocity()
{
	return velocity;
}

void VelocityBody::setDrag(OwnMathFuncs::Vector2 value)
{
	drag = value;
}

OwnMathFuncs::Vector2 VelocityBody::getDrag()
{
	return drag;
}

void VelocityBody::AddForce(OwnMathFuncs::Vector2 direction, float power)
{
	velocity.x += direction.x * power;
	velocity.y += direction.y * power;
}

OwnMathFuncs::Vector2 VelocityBody::getColliderWorldPosition()
{
	return collider->getWorldPosition();
}

void VelocityBody::resetVelocity()
{
	velocity = { 0, 0 };
}

VelocityBody::~VelocityBody()
{
}
