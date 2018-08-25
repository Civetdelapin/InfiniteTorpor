#include "PlayerController.h"

PlayerController::PlayerController(GameObject* game_object) : Component(game_object)
{

}


PlayerController::~PlayerController()
{


}

void PlayerController::update()
{

	OwnMathFuncs::Vector2 normalizeDirection = { 0, 0 };

	if (can_move) {
		const Uint8* keystates = SDL_GetKeyboardState(NULL);

		if (keystates[SDL_SCANCODE_W])
			normalizeDirection.y = -1;

		if (keystates[SDL_SCANCODE_S])
			normalizeDirection.y = 1;

		if (keystates[SDL_SCANCODE_A]) {
			normalizeDirection.x = -1;
		}

		if (keystates[SDL_SCANCODE_D]) {
			normalizeDirection.x = 1;
		}

		OwnMathFuncs::OwnMathFuncs::normalize(normalizeDirection);


		velocity.x += normalizeDirection.x * speed * Time::deltaTime;
		velocity.y += normalizeDirection.y * speed * Time::deltaTime;


		//Make the drag
		velocity.x += -drag * velocity.x * Time::deltaTime;
		if (fabs(velocity.x) < 1)
			velocity.x = 0.0f;

		velocity.y += -drag * velocity.y * Time::deltaTime;
		if (fabs(velocity.y) < 1)
			velocity.y = 0.0f;

	
		if (velocity.x < 0 && game_object->scale.x > 0) {
			game_object->scale.x *= -1;
		}
		else if (velocity.x > 0 && game_object->scale.x < 0) {
			game_object->scale.x *= -1;
		}
		

		// Clamp velocities
		if (velocity.x > 500.0f)
			velocity.x = 500.0f;

		if (velocity.x < -500.0f)
			velocity.x = -500.0f;

		if (velocity.y > 500.0f)
			velocity.y = 500.0f;

		if (velocity.y < -500.0f)
			velocity.y = -500.0f;


		//OwnMathFuncs::OwnMathFuncs::normalize(velocity);


		//std::cout << "v.x : " << velocity.x << ", v.y : " << velocity.y << std::endl;

	}
	



	float new_player_pos_x = game_object->position.x + (velocity.x * Time::deltaTime);
	float new_player_pos_y = game_object->position.y + (velocity.y * Time::deltaTime);


	/*

	//Test the collision with the tilemap
	if (velocity.x <= 0) // Moving Left
	{

		if (test_map->getTile(new_player_pos_x - ((game_object->sprite_sizeX / 2) - world_collider_left_offset) * scale_factor, position.y + ((sprite_sizeY / 2) - world_collider_up_offset) * scale_factor) != -1) {

			new_player_pos_x = position.x;
			velocity.x = 0;

		}

	}
	else // Moving Right
	{
		if (test_map->getTile(new_player_pos_x + ((sprite_sizeX / 2) - world_collider_right_offset) * scale_factor, position.y + ((sprite_sizeY / 2) - world_collider_up_offset) * scale_factor) != -1) {

			new_player_pos_x = position.x;
			velocity.x = 0;

		}
	}


	if (velocity.y <= 0) // Moving Up
	{
		if (test_map->getTile(position.x, new_player_pos_y + ((sprite_sizeY / 2) - world_collider_up_offset) * scale_factor) != -1) {

			new_player_pos_y = position.y;
			velocity.y = 0;

		}
	}
	else // Moving Down
	{
		if (test_map->getTile(position.x, new_player_pos_y + ((sprite_sizeY / 2) - world_collider_bottom_offset) * scale_factor) != -1) {

			new_player_pos_y = position.y;
			velocity.y = 0;

		}
	}
	*/


	game_object->position.x = new_player_pos_x;
	game_object->position.y = new_player_pos_y;
}
