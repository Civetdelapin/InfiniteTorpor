#include "PlayerAttack.h"
#include "Game.h"
#include "EnemyBasicBehavior.h"

PlayerAttack::PlayerAttack(GameObject* gameObject, BoxCollider* boxColliderAttack, BoxCollider* boxColliderAttackUp, BoxCollider* boxColliderAttackCorner, PlayerController* playerController, VelocityBody* velocityBody) : Component(gameObject), boxColliderAttack(boxColliderAttack), playerController(playerController), velocityBody(velocityBody), boxColliderAttackUp(boxColliderAttackUp), boxColliderAttackCorner(boxColliderAttackCorner)
{
	cancelAttackColliders();

	boxColliderAttackUpDownOffset = abs(boxColliderAttackUp->offset.y);

	boxColliderAttackCornerOffset = abs(boxColliderAttackCorner->offset.y);
}


PlayerAttack::~PlayerAttack()
{



}

void PlayerAttack::start()
{
	playerBehavior = gameObject->getRootParent()->getComponentInChildren<PlayerBehavior>();
}

void PlayerAttack::update()
{
	manageNormalizeDirection();
	manageAttackButton();
	
	if (state == State::attacking) {

		timeLeft -= Time::deltaTime;

		if (timeLeft <= 0) {

			if (nb_combo >= nbComboMax) {
				nb_combo = 0;
				state = State::cant_attack;
				timeLeft = timeAttackCd;
			}
			else {
				state = State::between_attack;

				timeLeftCancelCombo = timeAttackCancelCombo;
				
			}

			cancelAttackColliders();

			playerController->setCanMove(true);
		}
	}

	if (state == State::between_attack) {

		timeLeftCancelCombo -= Time::deltaTime;

		if (timeLeftCancelCombo <= 0) {

			nb_combo = 0;
			state = State::ready_attack;
		}
	}

	if (state == State::cant_attack) {

		timeLeft -= Time::deltaTime;

		if (timeLeft <= 0) {
			state = State::ready_attack;
		}
	}
		
	if (getActiveCollider() != nullptr) {

		
		//We tried to find if we hit someone
		std::vector<Collider*> vect = Game::instance()->getColliderManager()->isTrigger(getActiveCollider());
		if (vect.size() > 0) {

			for (Collider* collider : vect) {
				if (std::find(gameObjectsTouched.begin(), gameObjectsTouched.end(), collider->getGameObject()) == gameObjectsTouched.end()) {

					if (collider->getGameObject()->tag == "Enemy") {

						EnemyBasicBehavior* enemyBehavior = collider->getGameObject()->getRootParent()->getComponentInChildren<EnemyBasicBehavior>();
						if (enemyBehavior != nullptr) {
							
							if (enemyBehavior->takeDamage(normalizeDirection, velocityAttack * 0.80, attackDamage[nb_combo - 1], timeEnemyStun)) {
								
								//We have killed the enemy
								playerBehavior->addScore(enemyBehavior->getScoreValue());

							}

						}
						enemyBehavior = NULL;

						Game::instance()->getCamera()->startShake(10, 15, 0.15);
					}


					gameObjectsTouched.push_back(collider->getGameObject());
				}
			}
		
		}
	}
}

void PlayerAttack::clean()
{
	gameObjectsTouched.clear();
	Component::clean();
}

void PlayerAttack::attackButtonPressed()
{
	if ((state == State::ready_attack || state == State::between_attack) && playerController->getState() != PlayerController::State::dashing) {

		const Uint8* keystates = SDL_GetKeyboardState(NULL);
		
		if (normalizeDirection.y != 0 && normalizeDirection.y != gameObject->getRootParent()->getComponentInChildren<PlayerController>()->getDirection().y) {
			normalizeDirection.y = gameObject->getRootParent()->getComponentInChildren<PlayerController>()->getDirection().y;
		}

		if (normalizeDirection.x != 0 && normalizeDirection.x != gameObject->getRootParent()->getComponentInChildren<PlayerController>()->getDirection().x) {
			normalizeDirection.x = gameObject->getRootParent()->getComponentInChildren<PlayerController>()->getDirection().x;
		}

		activeAttackColliders();

		playerController->setCanMove(false);

		gameObjectsTouched.clear();

		state = State::attacking;

		timeLeft = timeAttackUp;

		nb_combo++;

		OwnMathFuncs::Vector2 vec_normalized = OwnMathFuncs::OwnMathFuncs::getNormalize(normalizeDirection);

		velocityBody->AddForce(vec_normalized, velocityAttack);
	}
}

void PlayerAttack::cancelAttackColliders()
{
	boxColliderAttackUp->setActive(false);
	boxColliderAttack->setActive(false);
	boxColliderAttackCorner->setActive(false);
}

void PlayerAttack::activeAttackColliders()
{
	if (normalizeDirection.x == 0) {
		if (normalizeDirection.y > 0) {
			boxColliderAttackUp->offset.y = boxColliderAttackUpDownOffset;
		}
		else {
			boxColliderAttackUp->offset.y = -boxColliderAttackUpDownOffset;
		}

		boxColliderAttackUp->setActive(true);
	}
	else if(abs(normalizeDirection.x) > 0 && abs(normalizeDirection.y) > 0)  {
		if (normalizeDirection.y > 0) {
			boxColliderAttackCorner->offset.y = boxColliderAttackCornerOffset;
		}
		else {
			boxColliderAttackCorner->offset.y = -boxColliderAttackCornerOffset;
		}

		boxColliderAttackCorner->setActive(true);
	}
	else {
		boxColliderAttack->setActive(true);
	}

}

BoxCollider * PlayerAttack::getActiveCollider()
{
	if (boxColliderAttack->isActive()) {
		return boxColliderAttack;
	}

	if (boxColliderAttackCorner->isActive()) {
		return boxColliderAttackCorner;
	}

	if (boxColliderAttackUp->isActive()) {
		return boxColliderAttackUp;
	}
	return nullptr;
}


void PlayerAttack::manageNormalizeDirection()
{
	

	if (Game::instance()->event.type == SDL_KEYDOWN && (Game::instance()->event.key.keysym.sym == SDLK_UP || Game::instance()->event.key.keysym.sym == SDLK_DOWN || Game::instance()->event.key.keysym.sym == SDLK_LEFT || Game::instance()->event.key.keysym.sym == SDLK_RIGHT)) {

		
		normalizeDirection = gameObject->getRootParent()->getComponentInChildren<PlayerController>()->getDirection();

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