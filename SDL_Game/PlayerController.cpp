#include "PlayerController.h"
#include "Game.h"

PlayerController::PlayerController(GameObject* gameObject) : Component(gameObject)
{

	velocityBody = gameObject->getComponent<VelocityBody>();
	animator = gameObject->getComponent<Animator>();
	boxCollider = gameObject->getComponent<BoxCollider>();

}


PlayerController::~PlayerController()
{


}

void PlayerController::setCanMove(bool value)
{
	canMove = value;
}

void PlayerController::update()
{
	float cur_speed = speed * abs(gameObject->getWorldScale().x);
	float cur_dash_spped = dashSpeed * abs(gameObject->getWorldScale().x);

	if (canMove && velocityBody != nullptr) {
		
		if (state != State::dashing) {

			normalizeDirection = { 0, 0 };

			const Uint8* keystates = SDL_GetKeyboardState(NULL);

			if (keystates[SDL_SCANCODE_UP])
				normalizeDirection.y += -1;

			if (keystates[SDL_SCANCODE_DOWN])
				normalizeDirection.y += 1;

			if (keystates[SDL_SCANCODE_LEFT]) {
				normalizeDirection.x += -1;
			}

			if (keystates[SDL_SCANCODE_RIGHT]) {
				normalizeDirection.x += 1;
			}

			if (normalizeDirection.x != 0) {
				direction.x = normalizeDirection.x;
			}

			if (normalizeDirection.y != 0) {
				direction.y = normalizeDirection.y;
			}
			

			OwnMathFuncs::OwnMathFuncs::normalize(normalizeDirection);

			//std::cout << normalizeDirection.x << ", "<< normalizeDirection.y << std::endl;

			velocityBody->AddForce(normalizeDirection, cur_speed * Time::deltaTime);
			


			if (velocityBody->getVelocity().x < 0 && gameObject->getWorldScale().x > 0) {
				gameObject->localScale.x *= -1;
			}
			else if (velocityBody->getVelocity().x > 0 && gameObject->getWorldScale().x < 0) {
				gameObject->localScale.x *= -1;
			}

			//std::cout << velocityBody->drag.x << std::endl;

			if (state != State::cant_dash) {

				if (keystates[SDL_SCANCODE_LCTRL]) {

					state = State::dashing;
					timeLeft = timeDash;

					gameObject->getComponent<PlayerBehavior>()->setInvicible(timeInvisibleDash);

					if (normalizeDirection.x == 0 && normalizeDirection.y == 0) {
						
						//We dash where the player is looking
						normalizeDirection.x = gameObject->getWorldScale().x;
						OwnMathFuncs::OwnMathFuncs::normalize(normalizeDirection);
					}
				}
			}
			else {
				timeLeft -= Time::deltaTime;

				if (timeLeft <= 0) {
					state = State::ready_dash;
				}
			}

		}
		else {

			//std::cout << normalizeDirection.x << ", " << normalizeDirection.y << std::endl;

			OwnMathFuncs::OwnMathFuncs::normalize(normalizeDirection);
			velocityBody->AddForce(normalizeDirection, cur_dash_spped * Time::deltaTime);
			
			timeLeft -= Time::deltaTime;
			if (timeLeft <= 0) {
				state = State::cant_dash;
				timeLeft = timeCDDash;
			}
		}

	}

	//std::cout << "velocity x : " << velocityBody->velocity.x << ", velocity y : " << velocityBody->velocity.y << std::endl;

	if (canMove) {

		if (abs(velocityBody->getVelocity().x) > 3 || abs(velocityBody->getVelocity().y) > 3) {
			animator->play("Walking");
		}
		else {
			animator->play("Idle");
		}
	}
}

PlayerController::State PlayerController::getState()
{
	return state;
}

OwnMathFuncs::Vector2 PlayerController::getDirection()
{
	return direction;
}
