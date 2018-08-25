#include "Player.h"


Player::Player(SDL_Renderer* renderer, Map* test_map) : GameObject(renderer), test_map(test_map)
{
	PlayerController* playerController = new PlayerController(this);
	addComponent(playerController);

}


Player::~Player()
{
}

void Player::update()
{
	GameObject::update();
}
