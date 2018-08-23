#include "Player.h"


Player::Player(SDL_Renderer* renderer) : GameObject(renderer)
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
	if (keystates[SDL_SCANCODE_A])
		velocity.x = -1;
	if (keystates[SDL_SCANCODE_S])
		velocity.y = 1;
	if (keystates[SDL_SCANCODE_D])
		velocity.x = 1;



	/*
	if (Game::event.type == SDL_KEYDOWN) {

		switch (Game::event.key.keysym.sym) {

		case SDLK_z:
			velocity.y = -speed;
			break;

		case SDLK_s:
			velocity.y = speed;
			break;

		case SDLK_q:
			velocity.x = -speed;
			break;

		case SDLK_d:
			velocity.x = speed;
			break;
		}
	}


	if (Game::event.type == SDL_KEYUP) {

		switch (Game::event.key.keysym.sym) {

		case SDLK_z:
			velocity.y = 0;
			break;

		case SDLK_s:
			velocity.y = 0;
			break;

		case SDLK_q:
			velocity.x = 0;
			break;

		case SDLK_d:
			velocity.x = 0;
			break;
		}
	}

	*/

	OwnMathFuncs::OwnMathFuncs::normalize(velocity);
	
	velocity.x *= speed;
	velocity.y *= speed;

	GameObject::update();
}
