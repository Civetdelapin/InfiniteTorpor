#include "Player.h"


Player::Player(SDL_Renderer* renderer, Map* test_map) : GameObject(renderer), test_map(test_map)
{
	
}


Player::~Player()
{
}

void Player::update()
{
	velocity.x = 0;
	velocity.y = 0;

	const Uint8* keystates = SDL_GetKeyboardState(NULL);

	if (keystates[SDL_SCANCODE_W])
		velocity.y = -1;

	if (keystates[SDL_SCANCODE_S])
		velocity.y = 1;

	if (keystates[SDL_SCANCODE_A]) {
		velocity.x = -1; 
		isFlipped = true;
	}
		
	if (keystates[SDL_SCANCODE_D]) {
		velocity.x = 1;
		isFlipped = false;
	}
	
	OwnMathFuncs::OwnMathFuncs::normalize(velocity);
	velocity.x *= speed;
	velocity.y *= speed;

	float new_player_pos_x = position.x + (velocity.x * Time::deltaTime);
	float new_player_pos_y = position.y + (velocity.y * Time::deltaTime);

	//Test the collision with the tilemap
	if (velocity.x <= 0) // Moving Left
	{
	
		if (test_map->getTile(new_player_pos_x, position.y) != -1) {
			
			new_player_pos_x = position.x;
			velocity.x = 0;

		}

	}
	else // Moving Right
	{
		if (test_map->getTile(new_player_pos_x, position.y) != -1) {

			new_player_pos_x = position.x;
			velocity.x = 0;

		}
	}


	if (velocity.y <= 0) // Moving Up
	{
		if (test_map->getTile(position.x, new_player_pos_y) != -1) {

			new_player_pos_y = position.y;
			velocity.y = 0;

		}
	}
	else // Moving Down
	{
		if (test_map->getTile(position.x, new_player_pos_y) != -1) {

			new_player_pos_y = position.y;
			velocity.y = 0;

		}
	}




	position.x = new_player_pos_x;
	position.y = new_player_pos_y;

	GameObject::update();
}
