#include "PlayerAttack.h"
#include "Game.h"
#include "EnemyBasicBehavior.h"

PlayerAttack::PlayerAttack(GameObject* game_object, BoxCollider* box_collider_attack, BoxCollider* box_coolider_attack_up, BoxCollider* box_collider_attack_corner, PlayerController* player_controller, VelocityBody* velocity_body) : Component(game_object), box_collider_attack(box_collider_attack), player_controller(player_controller), velocity_body(velocity_body), box_coolider_attack_up(box_coolider_attack_up), box_collider_attack_corner(box_collider_attack_corner)
{
	cancelAttackColliders();

	box_collider_attack_up_down_offset = abs(box_coolider_attack_up->offset.y);

	box_collider_attack_corner_offset = abs(box_collider_attack_corner->offset.y);
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

			cancelAttackColliders();

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
		
	if (getActiveCollider() != nullptr) {

		
		//We tried to find if we hit someone
		std::vector<Collider*> vect = Game::instance()->collider_manager->isTrigger(getActiveCollider());
		if (vect.size() > 0) {

			for (Collider* collider : vect) {
				if (std::find(game_objects_touched.begin(), game_objects_touched.end(), collider->game_object) == game_objects_touched.end()) {

					if (collider->game_object->tag == "Enemy") {

						EnemyBasicBehavior* enemy_stat = collider->game_object->getRootParent()->getComponent<EnemyBasicBehavior>();
						if (enemy_stat != nullptr) {	
							enemy_stat->takeDamage(normalizeDirection, velocity_attack * 0.80, attack_dmg[nb_combo - 1], time_enemy_stun);
						}
						enemy_stat = NULL;

						Game::instance()->getCamera()->startShake(10, 15, 0.25);
					}


					game_objects_touched.push_back(collider->game_object);	
				}
			}
		
		}
	}
}

void PlayerAttack::attackButtonPressed()
{
	if (state == State::ready_attack || state == State::between_attack) {

		const Uint8* keystates = SDL_GetKeyboardState(NULL);
		
		if (normalizeDirection.y != 0 && normalizeDirection.y != game_object->getRootParent()->getComponent<PlayerController>()->direction.y) {
			normalizeDirection.y = game_object->getRootParent()->getComponent<PlayerController>()->direction.y;
		}

		if (normalizeDirection.x != 0 && normalizeDirection.x != game_object->getRootParent()->getComponent<PlayerController>()->direction.x) {
			normalizeDirection.x = game_object->getRootParent()->getComponent<PlayerController>()->direction.x;
		}

		activeAttackColliders();

		player_controller->can_move = false;

		game_objects_touched.clear();

		state = State::attacking;

		time_passed = time_attack_up;

		nb_combo++;

		OwnMathFuncs::Vector2 vec_normalized = OwnMathFuncs::OwnMathFuncs::getNormalize(normalizeDirection);

		velocity_body->velocity.x += vec_normalized.x * velocity_attack * Time::deltaTime;
		velocity_body->velocity.y += vec_normalized.y * velocity_attack * Time::deltaTime;
	}
}

void PlayerAttack::cancelAttackColliders()
{
	box_coolider_attack_up->is_active = false;
	box_collider_attack->is_active = false;
	box_collider_attack_corner->is_active = false;
}

void PlayerAttack::activeAttackColliders()
{
	if (normalizeDirection.x == 0) {
		if (normalizeDirection.y > 0) {
			box_coolider_attack_up->offset.y = box_collider_attack_up_down_offset;
		}
		else {
			box_coolider_attack_up->offset.y = -box_collider_attack_up_down_offset;
		}

		box_coolider_attack_up->is_active = true;
	}
	else if(abs(normalizeDirection.x) > 0 && abs(normalizeDirection.y) > 0)  {
		if (normalizeDirection.y > 0) {
			box_collider_attack_corner->offset.y = box_collider_attack_corner_offset;
		}
		else {
			box_collider_attack_corner->offset.y = -box_collider_attack_corner_offset;
		}

		box_collider_attack_corner->is_active = true;
	}
	else {
		box_collider_attack->is_active = true;
	}

}

BoxCollider * PlayerAttack::getActiveCollider()
{
	if (box_collider_attack->is_active) {
		return box_collider_attack;
	}

	if (box_collider_attack_corner->is_active) {
		return box_collider_attack_corner;
	}

	if (box_coolider_attack_up->is_active) {
		return box_coolider_attack_up;
	}
	return nullptr;
}


void PlayerAttack::manageNormalizeDirection()
{
	

	if (Game::instance()->event.type == SDL_KEYDOWN && (Game::instance()->event.key.keysym.sym == SDLK_UP || Game::instance()->event.key.keysym.sym == SDLK_DOWN || Game::instance()->event.key.keysym.sym == SDLK_LEFT || Game::instance()->event.key.keysym.sym == SDLK_RIGHT)) {

		
		normalizeDirection = game_object->getRootParent()->getComponent<PlayerController>()->direction;

		//Managing the normalize direction
		const Uint8* keystates = SDL_GetKeyboardState(NULL);
		
		if (!keystates[SDL_SCANCODE_UP] && !keystates[SDL_SCANCODE_DOWN]) {
			normalizeDirection.y = 0;
		}

		
		if (!keystates[SDL_SCANCODE_LEFT] && !keystates[SDL_SCANCODE_RIGHT]) {
			normalizeDirection.x = 0;
		}
		
		
		//OwnMathFuncs::OwnMathFuncs::normalize(normalizeDirection);

		//std::cout << "X : " << normalizeDirection.x << ", Y : " << normalizeDirection.y << std::endl;

		if (abs(normalizeDirection.x) < 0.1) {
			normalizeDirection.x = 0;
		}

		if (abs(normalizeDirection.y) < 0.1) {
			normalizeDirection.y = 0;
		}
		
	}
	
}


void PlayerAttack::manageAttackButton()
{
	switch (Game::instance()->event.type) {
	case SDL_KEYDOWN:
		switch (Game::instance()->event.key.keysym.sym) {
		case SDLK_SPACE:
			if (!button_pressed) {
				attackButtonPressed();
				button_pressed = true;
			}
			break;
		}
		break;

	case SDL_KEYUP:
		switch (Game::instance()->event.key.keysym.sym) {
		case SDLK_SPACE:
			button_pressed = false;
			break;
		}
		break;

	default:
		break;
	}
}