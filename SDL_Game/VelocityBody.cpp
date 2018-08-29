#include "VelocityBody.h"
#include "Game.h"

VelocityBody::VelocityBody(GameObject* game_object) : Component(game_object)
{

	collider = game_object->getComponent<Collider>();

}

float clip(float n, float lower, float upper) {
	return std::max(lower, std::min(n, upper));
}


void VelocityBody::update()
{
	/*
	float dragForceMagnitudeX = pow(OwnMathFuncs::OwnMathFuncs::magnitude(velocity),2) * drag.x;
	float dragForceMagnitudeY = pow(OwnMathFuncs::OwnMathFuncs::magnitude(velocity), 2) * drag.y;
	*/

	//Make the drag
	velocity.x = velocity.x * clip(1 - Time::deltaTime * drag.x, 0, 1);
	if (fabs(velocity.x) < 0.1)
		velocity.x = 0.0f;

	velocity.y = velocity.y * clip(1 - Time::deltaTime * drag.x, 0, 1);
	if (fabs(velocity.y) < 0.1)
		velocity.y = 0.0f;

	//std::cout << velocity.x << std::endl;

	if (velocity.x < 0 && game_object->getWorldScale().x > 0) {
		game_object->local_scale.x *= -1;
	}
	else if (velocity.x > 0 && game_object->getWorldScale().x < 0) {
		game_object->local_scale.x *= -1;
	}

	/*
	// Clamp velocities
	if (velocity.x > 500.0f)
	velocity.x = 500.0f;

	if (velocity.x < -500.0f)
	velocity.x = -500.0f;

	if (velocity.y > 500.0f)
	velocity.y = 500.0f;

	if (velocity.y < -500.0f)
	velocity.y = -500.0f;
	*/

	//Collision detection
	if (velocity.x != 0) {
		float new_player_pos_x = game_object->local_position.x + (velocity.x * Time::deltaTime);

		//Save the old position in casse we need resolve collision
		float old_player_pos_x = game_object->local_position.x;

		game_object->local_position.x = new_player_pos_x;
		if (collider != nullptr) {

			std::vector<Collider*> vect = Game::collider_manager->isTrigger(collider);
			if (vect.size() > 0) {
				game_object->local_position.x = old_player_pos_x;
				velocity.x = 0;
			}
		}
	}

	if (velocity.y != 0) {
		float new_player_pos_y = game_object->local_position.y + (velocity.y * Time::deltaTime);

		//Save the old position in casse we need resolve collision
		float old_player_pos_y = game_object->local_position.y;

		game_object->local_position.y = new_player_pos_y;
		if (collider != nullptr) {

			std::vector<Collider*> vect = Game::collider_manager->isTrigger(collider);
			if (vect.size() > 0) {
				game_object->local_position.y = old_player_pos_y;
				velocity.y = 0;
			}
		}
	}


}

VelocityBody::~VelocityBody()
{
}
