#include "PlayerStat.h"
#include "Game.h"

#include "Animator.h";
#include "DisplayScreenFadeInOut.h"
#include "PlayerController.h"

PlayerStat::PlayerStat(GameObject* game_object) : Component(game_object)
{
}


PlayerStat::~PlayerStat()
{
}

float PlayerStat::getMaxHp()
{
	return max_hp;
}

float PlayerStat::getCurHP()
{
	return cur_hp;
}


void PlayerStat::start()
{
	time_passed_score = time_loose_score;

}

void PlayerStat::update()
{	
	if (is_invicible) {

		time_passed -= Time::deltaTime;

		if (time_passed <= 0) {
			is_invicible = false;
		}
	}

	if (is_dying) {

	}


	time_passed_score -= Time::deltaTime;
	if (time_passed_score <= 0) {
		score -= 1;
		time_passed_score = time_loose_score;
	}
}

void PlayerStat::setInvicible(float time)
{
	is_invicible = true;
	time_passed = time;
}

void PlayerStat::setDying()
{
	is_dying = true;

	Game::instance()->findGameObject("UI_Manager")->getComponent<DisplayScreenFadeInOut>()->setState(DisplayScreenFadeInOut::FadingIn);
	game_object->getComponent<SpriteRenderer>()->setLayer(RendererManager::MAX_LAYER);

	game_object->getComponent<PlayerController>()->setCanMove(false);
	game_object->getComponent<Animator>()->play("Dying");

	Game::instance()->getCamera()->setObjectToFollow(game_object);
}

bool PlayerStat::addDamage(float dmg)
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

int PlayerStat::getScore()
{
	return score;
}

void PlayerStat::addScore(int value)
{
	score += value;
}
