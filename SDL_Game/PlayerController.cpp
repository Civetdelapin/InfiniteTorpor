#include "PlayerController.h"
#include "Game.h"

PlayerController::PlayerController(GameObject* game_object) : Component(game_object)
{

	velocityBody = game_object->getComponent<VelocityBody>();
	animator = game_object->getComponent<Animator>();
	box_collider = game_object->getComponent<BoxCollider>();

	if (velocityBody == nullptr) {
		velocityBody = new VelocityBody(game_object);
	}
	
}


PlayerController::~PlayerController()
{


}

void PlayerController::update()
{

	float cur_speed = speed * abs(game_object->getWorldScale().x);
	float cur_dash_spped = dash_speed * abs(game_object->getWorldScale().x);

	if (can_move && velocityBody != nullptr) {
		
		if (state != State::dashing) {

			normalizeDirection = { 0, 0 };

			const Uint8* keystates = SDL_GetKeyboardState(NULL);

			if (keystates[SDL_SCANCODE_UP])
				normalizeDirection.y = -1;

			if (keystates[SDL_SCANCODE_DOWN])
				normalizeDirection.y = 1;

			if (keystates[SDL_SCANCODE_LEFT]) {
				normalizeDirection.x = -1;
			}

			if (keystates[SDL_SCANCODE_RIGHT]) {
				normalizeDirection.x = 1;
			}

			OwnMathFuncs::OwnMathFuncs::normalize(normalizeDirection);

			//std::cout << normalizeDirection.x << ", "<< normalizeDirection.y << std::endl;

			velocityBody->velocity.x += normalizeDirection.x * cur_speed * Time::deltaTime;
			velocityBody->velocity.y += normalizeDirection.y * cur_speed * Time::deltaTime;

			//std::cout << velocityBody->drag.x << std::endl;

			if (state != State::cant_dash) {

				if (keystates[SDL_SCANCODE_LCTRL]) {

					state = State::dashing;
					time_passed = time_dash;

					if (normalizeDirection.x == 0 && normalizeDirection.y == 0) {
						
						//We dash where the player is looking
						normalizeDirection.x = game_object->getWorldScale().x;
						OwnMathFuncs::OwnMathFuncs::normalize(normalizeDirection);
					}
				}
			}
			else {
				time_passed -= Time::deltaTime;

				if (time_passed <= 0) {
					state = State::ready_dash;
				}
			}

		}
		else {

			//std::cout << normalizeDirection.x << ", " << normalizeDirection.y << std::endl;

			OwnMathFuncs::OwnMathFuncs::normalize(normalizeDirection);

			velocityBody->velocity.x += normalizeDirection.x * cur_dash_spped * Time::deltaTime;
			velocityBody->velocity.y += normalizeDirection.y * cur_dash_spped * Time::deltaTime;

			time_passed -= Time::deltaTime;

			if (time_passed <= 0) {
				state = State::cant_dash;

				time_passed = time_cd_dash;
			}
		}

	}


	

	//std::cout << "velocity x : " << velocityBody->velocity.x << ", velocity y : " << velocityBody->velocity.y << std::endl;

	if (abs(velocityBody->velocity.x) > 3 || abs(velocityBody->velocity.y) > 3) {
		animator->play("Walking");
	}
	else {
		animator->play("Idle");
	}
}
