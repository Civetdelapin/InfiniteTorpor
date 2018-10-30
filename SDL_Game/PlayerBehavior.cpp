#include "PlayerBehavior.h"
#include "Game.h"

#include "Animator.h";
#include "DisplayScreenFadeInOut.h"
#include "PlayerController.h"
#include "GameManager.h"

PlayerBehavior::PlayerBehavior(GameObject* gameObject) : Component(gameObject)
{
}


PlayerBehavior::~PlayerBehavior()
{
}

float PlayerBehavior::getMaxHp()
{
	return maxHealthPoint;
}

float PlayerBehavior::getCurHP()
{
	return currentHealthPoint;
}


void PlayerBehavior::start()
{
	timeLeftScore = timeBeforeLoosingScore;

}

void PlayerBehavior::update()
{
	if (state == playing) {

		if (invicible) {

			timeLeft -= Time::deltaTime;

			if (timeLeft <= 0) {
				invicible = false;
			}
		}

		timeLeftScore -= Time::deltaTime;
		if (timeLeftScore <= 0 && score > 0) {
			score -= 1;
			timeLeftScore = timeBeforeLoosingScore;
		}

		
		switch (Game::instance()->event.type) {
			case SDL_KEYUP:
				inputUp = true;
				break;
			case SDL_KEYDOWN:
				switch (Game::instance()->event.key.keysym.sym) {
					case SDLK_ESCAPE:
						
						if (inputUp) {
							inputUp = false;
							Game::instance()->findGameObject("UI_Manager")->getComponentInChildren<DisplayGamePause>()->pause();
						}
						break;
					}
				break;
		}
	}
	else if (state == spawning) {
		timeLeft -= Time::deltaTime;

		if (timeLeft <= 0) {
			state = playing;

			gameObject->getComponent<PlayerController>()->setCanMove(true);
		}
	}
}

void PlayerBehavior::setInvicible(float time)
{
	invicible = true;
	timeLeft = time;
}

void PlayerBehavior::startLevel()
{
	gameObject->getComponent<SpriteRenderer>()->setLayer(PlayerBehavior::PLAYER_LAYER);
	
	gameObject->getComponent<Animator>()->play("WakingUp");
	gameObject->getComponent<PlayerController>()->setCanMove(false);

	timeLeft = timeSpawn;
	state = spawning;

	gameObject->getComponent<PlayerController>()->resetPlayerController();
}

void PlayerBehavior::endLevel()
{
	gameObject->getComponent<PlayerController>()->setCanMove(false);
	gameObject->getComponent<Animator>()->play("Dying");

	state = endingLevel;
}

void PlayerBehavior::restartGame()
{
	currentHealthPoint = maxHealthPoint;
	score = 0;

	dying = false;
}

void PlayerBehavior::setDying()
{
	dying = true;
	gameObject->getComponent<SpriteRenderer>()->setLayer(RendererManager::MAX_LAYER);
	gameObject->getComponent<PlayerController>()->setCanMove(false);

	gameObject->getComponent<Animator>()->play("Dying");

	state = endingLevel;

	Game::instance()->findGameObject("Manager")->getComponent<GameManager>()->gameOver(score);
}

bool PlayerBehavior::addDamage(float dmg)
{
	if (!invicible) {
		
		currentHealthPoint -= dmg;
		
		if (currentHealthPoint <= 0) {

			if (!dying) {
				setDying();
			}

		}
		else {
			Game::instance()->getCamera()->startShake(25, 20, 0.75f);
		}

		setInvicible(timeInvicible);

		return true;
	}

	return false;
}

int PlayerBehavior::getScore()
{
	return score;
}

void PlayerBehavior::addScore(int value)
{
	score += value;
}
