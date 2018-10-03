#include "ProjectileBehavior.h"
#include "Game.h"


ProjectileBehavior::ProjectileBehavior(GameObject* game_object, float speed, Collider* hitbox_collider) : Component(game_object), hitbox_collider(hitbox_collider), speed(speed)
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
		float new_player_pos_x = game_object->local_position.x + direction.x * (speed * Time::deltaTime);

		//Save the old position in casse we need resolve collision
		float old_player_pos_x = game_object->local_position.x;

		game_object->local_position.x = new_player_pos_x;
		if (hitbox_collider != nullptr) {

			std::vector<Collider*> vect = Game::instance()->collider_manager->isTrigger(hitbox_collider);
			if (vect.size() > 0 && vect[0]->getGameObject()->tag != "Player") {
				game_object->local_position.x = old_player_pos_x;
				direction.x = 0;

				Game::instance()->destroyGameObject(game_object);
			}
		}
	}

	if (direction.y != 0) {
		float new_player_pos_y = game_object->local_position.y + direction.y * (speed * Time::deltaTime);

		//Save the old position in casse we need resolve collision
		float old_player_pos_y = game_object->local_position.y;

		game_object->local_position.y = new_player_pos_y;
		if (hitbox_collider != nullptr) {

			std::vector<Collider*> vect = Game::instance()->collider_manager->isTrigger(hitbox_collider);
			if (vect.size() > 0 && vect[0]->getGameObject()->tag != "Player") {
				game_object->local_position.y = old_player_pos_y;
				direction.y = 0;

				Game::instance()->destroyGameObject(game_object);
			}
		}
	}


}
