#include "PlayerController.h"

PlayerController::PlayerController(GameObject* game_object) : Component(game_object)
{

}


PlayerController::~PlayerController()
{


}

void PlayerController::update()
{

	velocity.x = 0;
	velocity.y = 0;

	if (can_move) {
		const Uint8* keystates = SDL_GetKeyboardState(NULL);

		if (keystates[SDL_SCANCODE_W])
			velocity.y += -1;

		if (keystates[SDL_SCANCODE_S])
			velocity.y += 1;

		if (keystates[SDL_SCANCODE_A]) {
			velocity.x += -1;
		}

		if (keystates[SDL_SCANCODE_D]) {
			velocity.x += 1;
		}

		if (velocity.x < 0) {
			game_object->isFlipped = true;
		}
		else if (velocity.x > 0) {
			game_object->isFlipped = false;
		}

		OwnMathFuncs::OwnMathFuncs::normalize(velocity);
		velocity.x *= speed;
		velocity.y *= speed;
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
