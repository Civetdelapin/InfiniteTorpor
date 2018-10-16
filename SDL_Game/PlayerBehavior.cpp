#include "PlayerBehavior.h"
#include "Game.h"

#include "Animator.h";
#include "DisplayScreenFadeInOut.h"
#include "PlayerController.h"

PlayerBehavior::PlayerBehavior(GameObject* game_object) : Component(game_object)
{
}


PlayerBehavior::~PlayerBehavior()
{
}

float PlayerBehavior::getMaxHp()
{
	return max_hp;
}

float PlayerBehavior::getCurHP()
{
	return cur_hp;
}


void PlayerBehavior::start()
{
	timeLeft_score = time_loose_score;

}

void PlayerBehavior::update()
{
	if (state == playing) {

		if (is_invicible) {

			timeLeft -= Time::deltaTime;

			if (timeLeft <= 0) {
				is_invicible = false;
			}
		}

		if (is_dying) {

		}


		timeLeft_score -= Time::deltaTime;
		if (timeLeft_score <= 0) {
			score -= 1;
			timeLeft_score = time_loose_score;
		}
	}
	else if (state == spawning) {
		timeLeft -= Time::deltaTime;

		if (timeLeft <= 0) {
			state = playing;

			game_object->getComponent<PlayerController>()->setCanMove(true);
		}
	}
}

void PlayerBehavior::setInvicible(float time)
{
	is_invicible = true;
	timeLeft = time;
}

void PlayerBehavior::startLevel()
{
	game_object->getComponent<SpriteRenderer>()->setLayer(PlayerBehavior::PLAYER_LAYER);
	
	game_object->getComponent<Animator>()->play("WakingUp");
	game_object->getComponent<PlayerController>()->setCanMove(false);

	timeLeft = time_spawn;
	state = spawning;
}

void PlayerBehavior::endLevel()
{
	game_object->getComponent<PlayerController>()->setCanMove(false);

	game_object->getComponent<Animator>()->play("Dying");
}

void PlayerBehavior::setDying()
{
	is_dying = true;

	Game::instance()->findGameObject("UI_Manager")->getComponent<DisplayScreenFadeInOut>()->setState(DisplayScreenFadeInOut::FadingIn, DisplayScreenFadeInOut::TIME_FADE_DEAD);
	game_object->getComponent<SpriteRenderer>()->setLayer(RendererManager::MAX_LAYER);

	game_object->getComponent<PlayerController>()->setCanMove(false);
	game_object->getComponent<Animator>()->play("Dying");

	Game::instance()->getCamera()->setObjectToFollow(game_object);
}

bool PlayerBehavior::addDamage(float dmg)
{
	if (!is_invicible) {
		
		cur_hp -= dmg;
		
		if (cur_hp <= 0) {

			if (!is_dying) {
				setDying();
			}

		}
		else {
			Game::instance()->getCamera()->startShake(25, 20, 0.75f);
		}

		setInvicible(time_invicible);

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
