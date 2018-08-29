#include "PlayerAttack.h"
#include "Game.h"

PlayerAttack::PlayerAttack(GameObject* game_object, BoxCollider* box_collider_attack, PlayerController* player_controller, VelocityBody* velocity_body) : Component(game_object), box_collider_attack(box_collider_attack), player_controller(player_controller), velocity_body(velocity_body)
{
	box_collider_attack->is_active = false;
}


PlayerAttack::~PlayerAttack()
{



}

void PlayerAttack::update()
{
	manageNormalizeDirection();
	manageAttackButton();
	
	if (state == State::attacking) {

		time_passed -= Time::deltaTime;

		if (time_passed <= 0) {

			if (nb_combo >= nb_combo_max) {
				nb_combo = 0;
				state = State::cant_attack;
				time_passed = time_attack_cd;
			}
			else {
				state = State::between_attack;

				time_passed_cancel_combo = time_attack_cancel_combo;
				
			}

			box_collider_attack->is_active = false;
			player_controller->can_move = true;
		}
	}

	if (state == State::between_attack) {

		time_passed_cancel_combo -= Time::deltaTime;

		if (time_passed_cancel_combo <= 0) {

			nb_combo = 0;
			state = State::ready_attack;
		}
	}

	if (state == State::cant_attack) {

		time_passed -= Time::deltaTime;

		if (time_passed <= 0) {
			state = State::ready_attack;
		}
	}
		
		//We tried to find if we hit someone
		std::vector<Collider*> vect = Game::collider_manager->isTrigger(box_collider_attack);
		if (vect.size() > 0) {

			for (Collider* collider : vect) {
				if (std::find(game_objects_touched.begin(), game_objects_touched.end(), collider->game_object) == game_objects_touched.end()) {

					if (collider->game_object->tag == "Enemy") {
						std::cout << "COLLIDED ATTACK" << std::endl;
						collider->game_object->getRootParent()->getComponent<VelocityBody>()->velocity.x += normalizeDirection.x * velocity_attack * Time::deltaTime * 0.75;
						collider->game_object->getRootParent()->getComponent<VelocityBody>()->velocity.y += normalizeDirection.y * velocity_attack * Time::deltaTime * 0.75;
					}
					game_objects_touched.push_back(collider->game_object);	
				}
			}
		
		}
	
}

void PlayerAttack::attackButtonPressed()
{
	if (state == State::ready_attack || state == State::between_attack) {
		box_collider_attack->is_active = true;
		player_controller->can_move = false;

		game_objects_touched.clear();

		state = State::attacking;

		time_passed = time_attack_up;
		nb_combo++;

		velocity_body->velocity.x += normalizeDirection.x * velocity_attack * Time::deltaTime;
		velocity_body->velocity.y += normalizeDirection.y * velocity_attack * Time::deltaTime;
		
		Game::camera->startShake(10, 15, 0.25);
	}
}


void PlayerAttack::manageNormalizeDirection()
{
	//Managing the normalize direction
	const Uint8* keystates = SDL_GetKeyboardState(NULL);
	if (keystates[SDL_SCANCODE_UP]) {
		normalizeDirection.y = -1;
	}
	else {
		normalizeDirection.y = 0;
	}

	if (keystates[SDL_SCANCODE_DOWN] && normalizeDirection.y >= 0) {
		normalizeDirection.y = 1;
	}

	if (keystates[SDL_SCANCODE_LEFT]) {
		normalizeDirection.x = -1;
	}

	if (keystates[SDL_SCANCODE_RIGHT]) {
		normalizeDirection.x = 1;
	}

	OwnMathFuncs::OwnMathFuncs::normalize(normalizeDirection);

	if (abs(normalizeDirection.x) < 0.1) {
		normalizeDirection.x = 0;
	}
}


void PlayerAttack::manageAttackButton()
{
	switch (Game::event.type) {
	case SDL_KEYDOWN:
		switch (Game::event.key.keysym.sym) {
		case SDLK_SPACE:
			if (!button_pressed) {
				attackButtonPressed();
				button_pressed = true;
			}
			break;
		}
		break;

	case SDL_KEYUP:
		switch (Game::event.key.keysym.sym) {
		case SDLK_SPACE:
			button_pressed = false;
			break;
		}
		break;

	default:
		break;
	}
}




/*

if (state != State::attacking) {


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


if (ready_attack) {
switch (Game::event.type) {
case SDL_KEYDOWN:
switch (Game::event.key.keysym.sym) {
case SDLK_SPACE:
if (!button_pressed) {
box_collider_attack->is_active = true;
state = State::attacking;

player_controller->can_move = false;

time_passed = time_attack_up;



button_pressed = true;
}
break;
}
break;

case SDL_KEYUP:
switch (Game::event.key.keysym.sym) {
case SDLK_SPACE:
button_pressed = false;
break;
}
break;

default:
break;
}
}
else {
time_passed -= Time::deltaTime;

if (time_passed <= 0) {
state = State::ready_attack;
}
}

}
else {
time_passed -= Time::deltaTime;

velocity_body->velocity.x += normalizeDirection.x * velocity_attack * Time::deltaTime;
velocity_body->velocity.y += normalizeDirection.y * velocity_attack * Time::deltaTime;

if (time_passed <= 0) {
box_collider_attack->is_active = false;

state = State::ready_attack;
time_passed = time_attack_cd;

velocity_body->velocity.x *= 0.5f;
velocity_body->velocity.y *= 0.5f;

player_controller->can_move = true;
}
}
*/

